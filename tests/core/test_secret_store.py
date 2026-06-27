"""Tests for the secret store (P2-8): API key kept out of plaintext QSettings."""
import pytest

keyring = pytest.importorskip("keyring")
from keyring.backend import KeyringBackend

from autosar_configurator.utils import secret_store as ss


class _MemKeyring(KeyringBackend):
    priority = 1

    def __init__(self):
        self.store = {}

    def get_password(self, service, user):
        return self.store.get((service, user))

    def set_password(self, service, user, password):
        self.store[(service, user)] = password

    def delete_password(self, service, user):
        self.store.pop((service, user), None)


class _FakeSettings:
    def __init__(self):
        self.d = {}

    def value(self, k, default=None):
        return self.d.get(k, default)

    def setValue(self, k, v):
        self.d[k] = v

    def remove(self, k):
        self.d.pop(k, None)


@pytest.fixture
def mem_keyring():
    prev = keyring.get_keyring()
    keyring.set_keyring(_MemKeyring())
    yield
    keyring.set_keyring(prev)


def test_set_stores_in_keychain_not_plaintext(mem_keyring):
    st = _FakeSettings()
    ss.set_api_key(st, "secret123")
    assert "gemini_api_key" not in st.d  # no plaintext in QSettings
    assert ss.get_api_key(st) == "secret123"


def test_legacy_plaintext_is_migrated_and_scrubbed(mem_keyring):
    st = _FakeSettings()
    st.d["gemini_api_key"] = "legacyKey"  # simulate old plaintext
    assert ss.get_api_key(st) == "legacyKey"
    # migrated to keychain and scrubbed from QSettings
    assert "gemini_api_key" not in st.d
    assert keyring.get_password(ss.SERVICE_NAME, ss.KEY_NAME) == "legacyKey"


def test_empty_key_clears(mem_keyring):
    st = _FakeSettings()
    ss.set_api_key(st, "x")
    ss.set_api_key(st, "")
    assert ss.get_api_key(st) == ""
