"""
Tests for DBC Importer
Covers: DbcParser, DbcImporter (validate, preview, import, extended frames)
"""
import pytest
from pathlib import Path
from textwrap import dedent

from autosar_configurator.core.importers.dbc_importer import (
    DbcParser, DbcImporter, DbcDatabase, DbcMessage, DbcSignal,
)


# ---------------------------------------------------------------------------
# Fixtures: temporary DBC files
# ---------------------------------------------------------------------------

MINIMAL_DBC = dedent("""\
    VERSION ""

    NS_ :

    BS_:

    BU_: ECU1 ECU2

    BO_ 256 EngineStatus: 8 ECU1
     SG_ EngineRPM : 0|16@1+ (0.25,0) [0|16383.75] "rpm" ECU2,ECU3
     SG_ EngineTemp : 16|8@1+ (1,-40) [-40|215] "degC" ECU2

    BO_ 512 TransmissionData: 4 ECU1
     SG_ CurrentGear : 0|4@1+ (1,0) [0|8] "" ECU2
""")

EXTENDED_FRAME_DBC = dedent("""\
    VERSION ""

    NS_ :

    BS_:

    BU_: ECU1 ECU2

    BO_ 256 StandardMsg: 8 ECU1
     SG_ Sig1 : 0|8@1+ (1,0) [0|255] "" ECU2

    BO_ 2147484160 ExtendedMsg: 8 ECU1
     SG_ Sig2 : 0|16@1+ (1,0) [0|65535] "" ECU2
""")
# 2147484160 = 0x80000200 → extended frame, actual ID = 0x200 (512)

BIG_ENDIAN_SIGNED_DBC = dedent("""\
    VERSION ""

    NS_ :

    BS_:

    BU_: ECU1 ECU2

    BO_ 100 TestMsg: 8 ECU1
     SG_ BigEndianSig : 7|16@0+ (0.1,0) [0|6553.5] "rpm" ECU2
     SG_ SignedSig : 24|8@1- (1,-128) [-128|127] "val" ECU2
""")

EMPTY_DBC = dedent("""\
    VERSION ""

    NS_ :

    BS_:

    BU_:
""")

NEGATIVE_OFFSET_DBC = dedent("""\
    VERSION ""

    NS_ :

    BS_:

    BU_: ECU1 ECU2

    BO_ 300 SensorData: 8 ECU1
     SG_ Temperature : 0|16@1+ (0.01,-273.15) [-273.15|327.67] "degC" ECU2
     SG_ Pressure : 16|16@1+ (0.001,0) [0|65.535] "bar" ECU2
""")


@pytest.fixture
def tmp_dbc(tmp_path):
    """Helper to write DBC content to a temp file and return the path."""
    def _write(content: str, name: str = "test.dbc") -> Path:
        p = tmp_path / name
        p.write_text(content, encoding="utf-8")
        return p
    return _write


# ---------------------------------------------------------------------------
# DbcParser tests
# ---------------------------------------------------------------------------

class TestDbcParser:
    """Tests for the low-level DBC parser."""

    def test_parse_minimal(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        parser = DbcParser()
        messages = parser.parse(path)

        assert len(messages) == 2

        # First message
        msg1 = messages[0]
        assert msg1.id == 256
        assert msg1.name == "EngineStatus"
        assert msg1.dlc == 8
        assert msg1.transmitter == "ECU1"
        assert msg1.is_extended is False
        assert len(msg1.signals) == 2

        # Check signals
        rpm = msg1.signals[0]
        assert rpm.name == "EngineRPM"
        assert rpm.start_bit == 0
        assert rpm.length == 16
        assert rpm.byte_order == "little_endian"
        assert rpm.value_type == "unsigned"
        assert rpm.factor == 0.25
        assert rpm.offset == 0.0
        assert rpm.unit == "rpm"
        assert "ECU2" in rpm.receivers
        assert "ECU3" in rpm.receivers

        temp = msg1.signals[1]
        assert temp.name == "EngineTemp"
        assert temp.offset == -40.0
        assert temp.unit == "degC"

        # Second message
        msg2 = messages[1]
        assert msg2.id == 512
        assert msg2.name == "TransmissionData"
        assert msg2.dlc == 4
        assert len(msg2.signals) == 1

    def test_parse_extended_frame(self, tmp_dbc):
        """Extended frame IDs have bit 31 set; parser should strip it."""
        path = tmp_dbc(EXTENDED_FRAME_DBC)
        parser = DbcParser()
        messages = parser.parse(path)

        assert len(messages) == 2

        std_msg = messages[0]
        assert std_msg.id == 256
        assert std_msg.is_extended is False

        ext_msg = messages[1]
        assert ext_msg.id == 0x200  # bit 31 stripped: 0x80000200 → 0x200
        assert ext_msg.is_extended is True
        assert ext_msg.name == "ExtendedMsg"
        assert len(ext_msg.signals) == 1

    def test_parse_big_endian_and_signed(self, tmp_dbc):
        """Verify byte order and signed value type parsing."""
        path = tmp_dbc(BIG_ENDIAN_SIGNED_DBC)
        parser = DbcParser()
        messages = parser.parse(path)

        assert len(messages) == 1
        msg = messages[0]
        assert len(msg.signals) == 2

        big_sig = msg.signals[0]
        assert big_sig.name == "BigEndianSig"
        assert big_sig.byte_order == "big_endian"
        assert big_sig.value_type == "unsigned"
        assert big_sig.start_bit == 7

        signed_sig = msg.signals[1]
        assert signed_sig.name == "SignedSig"
        assert signed_sig.byte_order == "little_endian"
        assert signed_sig.value_type == "signed"
        assert signed_sig.offset == -128.0

    def test_parse_empty_dbc(self, tmp_dbc):
        """DBC with no messages should return empty list."""
        path = tmp_dbc(EMPTY_DBC)
        parser = DbcParser()
        messages = parser.parse(path)
        assert messages == []

    def test_parse_negative_offset(self, tmp_dbc):
        """Signals with negative offset and small factors."""
        path = tmp_dbc(NEGATIVE_OFFSET_DBC)
        parser = DbcParser()
        messages = parser.parse(path)

        assert len(messages) == 1
        temp_sig = messages[0].signals[0]
        assert temp_sig.factor == pytest.approx(0.01)
        assert temp_sig.offset == pytest.approx(-273.15)
        assert temp_sig.min_value == pytest.approx(-273.15)


# ---------------------------------------------------------------------------
# DbcImporter tests
# ---------------------------------------------------------------------------

class TestDbcImporter:
    """Tests for the high-level DbcImporter interface."""

    def test_supported_extensions(self):
        importer = DbcImporter()
        assert ".dbc" in importer.supported_extensions

    def test_format_name(self):
        importer = DbcImporter()
        assert "DBC" in importer.format_name

    def test_validate_valid_file(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        valid, error = importer.validate_file(path)
        assert valid is True
        assert error is None

    def test_validate_nonexistent_file(self):
        importer = DbcImporter()
        valid, error = importer.validate_file(Path("/nonexistent/file.dbc"))
        assert valid is False
        assert "not found" in error.lower()

    def test_validate_wrong_extension(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC, name="test.csv")
        importer = DbcImporter()
        valid, error = importer.validate_file(path)
        assert valid is False

    def test_validate_invalid_content(self, tmp_dbc):
        path = tmp_dbc("This is not a DBC file at all")
        importer = DbcImporter()
        valid, error = importer.validate_file(path)
        assert valid is False
        assert "valid DBC" in error

    def test_get_columns(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        columns = importer.get_columns(path)
        assert "MessageId" in columns
        assert "MessageName" in columns
        assert "DLC" in columns
        assert "IdType" in columns

    def test_get_signal_columns(self):
        importer = DbcImporter()
        cols = importer.get_signal_columns()
        assert "SignalName" in cols
        assert "StartBit" in cols
        assert "ByteOrder" in cols

    def test_preview_messages(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        records = importer.preview(path, limit=10)

        assert len(records) == 2
        assert records[0]["MessageName"] == "EngineStatus"
        assert records[0]["SignalCount"] == 2
        assert records[0]["IdType"] == "STANDARD"
        assert records[0]["DLC"] == 8

    def test_preview_extended_frame(self, tmp_dbc):
        path = tmp_dbc(EXTENDED_FRAME_DBC)
        importer = DbcImporter()
        records = importer.preview(path)

        std_rec = records[0]
        ext_rec = records[1]

        assert std_rec["IdType"] == "STANDARD"
        assert ext_rec["IdType"] == "EXTENDED"
        assert ext_rec["MessageId"] == "0x00000200"  # 8-digit hex for extended

    def test_preview_with_limit(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        records = importer.preview(path, limit=1)
        assert len(records) == 1

    def test_preview_signals(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        records = importer.preview_signals(path)

        assert len(records) == 3  # 2 signals in msg1 + 1 in msg2
        assert records[0]["SignalName"] == "EngineRPM"
        assert records[0]["ByteOrder"] == "little_endian"

    def test_preview_signals_filter_by_message(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        records = importer.preview_signals(path, message_name="EngineStatus")
        assert len(records) == 2
        assert all(r["MessageName"] == "EngineStatus" for r in records)

    def test_import_data_basic(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()

        mapping = {
            "MessageId": "CanObjectId",
            "MessageName": "SHORT-NAME",
            "DLC": "CanHwObjectCount",
        }

        result = importer.import_data(path, mapping)
        assert result.success is True
        assert result.records_imported == 2
        assert len(result.imported_data) == 2

        first = result.imported_data[0]
        assert first["CanObjectId"] == 256
        assert first["SHORT-NAME"] == "EngineStatus"
        assert first["CanHwObjectCount"] == 8
        # Signals should be preserved in _signals
        assert len(first["_signals"]) == 2

    def test_import_data_includes_id_type(self, tmp_dbc):
        path = tmp_dbc(EXTENDED_FRAME_DBC)
        importer = DbcImporter()

        mapping = {
            "MessageId": "CanObjectId",
            "IdType": "CanIdType",
        }

        result = importer.import_data(path, mapping)
        assert result.success is True

        std = result.imported_data[0]
        ext = result.imported_data[1]
        assert std["CanIdType"] == "STANDARD"
        assert ext["CanIdType"] == "EXTENDED"
        assert ext["CanObjectId"] == 0x200  # Stripped ID

    def test_import_data_empty_dbc(self, tmp_dbc):
        path = tmp_dbc(EMPTY_DBC)
        importer = DbcImporter()
        result = importer.import_data(path, {"MessageId": "id"})
        assert result.success is False
        assert result.records_imported == 0

    def test_get_messages(self, tmp_dbc):
        path = tmp_dbc(MINIMAL_DBC)
        importer = DbcImporter()
        messages = importer.get_messages(path)
        assert len(messages) == 2
        assert all(isinstance(m, DbcMessage) for m in messages)


class TestDbcDatabaseMetadata:
    def test_parse_database_metadata_enums_and_gb18030(self, tmp_path):
        dbc_text = dedent("""\
            VERSION ""
            NS_ :
            BS_:
            BU_: Tester VCU MCU

            BO_ 548 VCU_Cmd: 8 VCU
             SG_ VCU_En : 0|1@0+ (1,0) [0|1] "" MCU

            BO_ 551 MCU_Status: 8 MCU
             SG_ MCU_Temp : 7|8@0+ (1,-40) [-40|215] "℃" VCU

            BO_ 2015 DiagFunc: 8 Tester
             SG_ DiagData : 7|64@0+ (1,0) [0|0] "" MCU

            CM_ BO_ 551 "Inverter status frame";
            CM_ SG_ 551 MCU_Temp "Inverter temp";
            BA_DEF_ "BusType" STRING ;
            BA_DEF_ "DBName" STRING ;
            BA_DEF_ BO_ "GenMsgCycleTime" INT 0 60000;
            BA_DEF_ BO_ "GenMsgSendType" ENUM "Cyclic","Event";
            BA_DEF_ BO_ "VFrameFormat" ENUM "StandardCAN","StandardCAN_FD";
            BA_DEF_ BO_ "DiagRequest" INT 0 1;
            BA_DEF_ SG_ "GenSigStartValue" FLOAT 0 1000;
            BA_DEF_ SG_ "GenSigSendType" ENUM "Cyclic","OnChange";
            BA_DEF_DEF_ "BusType" "CAN";
            BA_DEF_DEF_ "GenMsgCycleTime" 0;
            BA_DEF_DEF_ "GenMsgSendType" "Cyclic";
            BA_DEF_DEF_ "VFrameFormat" "StandardCAN";
            BA_DEF_DEF_ "GenSigStartValue" 0;
            BA_DEF_DEF_ "GenSigSendType" "Cyclic";
            BA_ "BusType" "CAN FD";
            BA_ "DBName" "Powertrain";
            BA_ "GenMsgCycleTime" BO_ 551 10;
            BA_ "GenMsgSendType" BO_ 551 0;
            BA_ "VFrameFormat" BO_ 551 1;
            BA_ "DiagRequest" BO_ 2015 1;
            BA_ "GenSigStartValue" SG_ 551 MCU_Temp 40;
            BA_ "GenSigSendType" SG_ 551 MCU_Temp 1;
        """)
        path = tmp_path / "powertrain_gb18030.dbc"
        path.write_bytes(dbc_text.encode("gb18030"))

        parser = DbcParser()
        db = parser.parse_database(path)
        assert isinstance(db, DbcDatabase)
        assert db.ecu_nodes == ["Tester", "VCU", "MCU"]
        assert db.bus_type == "CAN FD"
        assert db.db_name == "Powertrain"

        by_name = {m.name: m for m in db.messages}
        assert by_name["VCU_Cmd"].is_fd is False
        mcu = by_name["MCU_Status"]
        assert mcu.is_fd is True
        assert mcu.cycle_time_ms == 10.0
        assert mcu.send_type == "Cyclic"
        assert mcu.comment == "Inverter status frame"
        sig = mcu.signals[0]
        assert sig.unit == "℃"
        assert sig.init_value == 40.0
        assert sig.send_type == "OnChange"
        assert sig.comment == "Inverter temp"

        diag = by_name["DiagFunc"]
        assert diag.is_diag is True
        assert diag.diag_role == "request"

        # Backwards-compatible parse() keeps returning List[DbcMessage]
        msgs_only = parser.parse(path)
        assert len(msgs_only) == 3
        assert all(isinstance(m, DbcMessage) for m in msgs_only)

    def test_parse_real_startapplication_mcu_dbc_readonly(self):
        real_dbc = Path(
            "/Users/qlwang/Desktop/未命名文件夹/mcuapp/Applications/SipAddon/StartApplication/DemoDatabase/MCU.dbc"
        )
        if not real_dbc.is_file():
            pytest.skip("External StartApplication MCU.dbc fixture not available")
        db = DbcParser().parse_database(real_dbc)
        assert "MCU" in db.ecu_nodes
        assert len(db.messages) >= 5
        assert any(m.cycle_time_ms and m.cycle_time_ms > 0 for m in db.messages)
        assert any(m.is_diag for m in db.messages)
        # Verify at least one signal with °C/℃ temperature unit decoded cleanly
        assert any("℃" in (s.unit or "") or "°C" in (s.unit or "") for m in db.messages for s in m.signals)
