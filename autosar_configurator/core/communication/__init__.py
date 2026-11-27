"""Pure-Python communication stack domain services, bit layout analyzer, and DBC sync."""

from .bit_layout import analyze_pdu_bit_layout, compute_signal_bits
from .dbc_sync import apply_dbc_sync, plan_dbc_sync
from .models import (
    CommChannelRow,
    CommDiagnostic,
    CommMessageRow,
    CommSignalRow,
    DbcSyncItem,
    DbcSyncPlan,
    DbcSyncResult,
    PduRRoutingRow,
)
from .service import (
    ANCHOR_PRIORITY,
    CAN_ID_TYPES,
    COMM_MODULES,
    COM_ENDIANNESS,
    COM_SIGNAL_TYPES,
    COM_TRANSFER_PROPS,
    COM_TX_MODES,
    CommunicationWorkbenchService,
)

__all__ = [
    "ANCHOR_PRIORITY",
    "CAN_ID_TYPES",
    "COMM_MODULES",
    "COM_ENDIANNESS",
    "COM_SIGNAL_TYPES",
    "COM_TRANSFER_PROPS",
    "COM_TX_MODES",
    "CommChannelRow",
    "CommDiagnostic",
    "CommMessageRow",
    "CommSignalRow",
    "CommunicationWorkbenchService",
    "DbcSyncItem",
    "DbcSyncPlan",
    "DbcSyncResult",
    "PduRRoutingRow",
    "analyze_pdu_bit_layout",
    "apply_dbc_sync",
    "compute_signal_bits",
    "plan_dbc_sync",
]
