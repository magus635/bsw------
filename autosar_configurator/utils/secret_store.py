"""Secret storage for sensitive values (e.g. the Gemini API key).

Addresses P2-8: previously the API key was written in plaintext to QSettings
(a world-readable plist on macOS / registry on Windows). This helper prefers
the OS keychain via the optional ``keyring`` package and only falls back to
QSettings when keyring is unavailable — emitting a one-time warning so the
plaintext fallback is never silent.

Usage::

    from autosar_configurator.utils.secret_store import get_api_key, set_api_key
    key = get_api_key(self.settings)
    set_api_key(self.settings, new_key)

When keyring is present, ``set_api_key`` also scrubs any legacy plaintext copy
left behind in QSettings.
"""
import logging

logger = logging.getLogger(__name__)

SERVICE_NAME = "AUTOSAR-DaVinciConfigurator"
KEY_NAME = "gemini_api_key"

_warned_fallback = False


def _keyring():
    """Return the keyring module if importable, else None (cached per-call is cheap)."""
    try:
        import keyring
        return keyring
    except Exception:
        return None


def _warn_once():
    global _warned_fallback
    if not _warned_fallback:
        _warned_fallback = True
        logger.warning(
            "python-keyring is not installed; the API key will be stored in "
            "QSettings (plaintext). Install 'keyring' to use the OS keychain."
        )


def get_api_key(settings) -> str:
    """Return the stored API key, preferring the OS keychain.

    Falls back to (and transparently migrates from) a legacy QSettings value.
    """
    kr = _keyring()
    if kr is not None:
        try:
            value = kr.get_password(SERVICE_NAME, KEY_NAME)
            if value:
                return value
            # Migrate a legacy plaintext value into the keychain, then scrub it.
            legacy = settings.value(KEY_NAME, "") if settings is not None else ""
            if legacy:
                try:
                    kr.set_password(SERVICE_NAME, KEY_NAME, legacy)
                    settings.remove(KEY_NAME)
                    logger.info("Migrated Gemini API key from QSettings to the OS keychain.")
                except Exception as e:
                    logger.warning("Failed to migrate API key to keychain: %s", e)
                return legacy
            return ""
        except Exception as e:
            logger.warning("Keychain read failed (%s); falling back to QSettings.", e)

    _warn_once()
    return settings.value(KEY_NAME, "") if settings is not None else ""


def set_api_key(settings, key: str) -> None:
    """Store the API key, preferring the OS keychain.

    When keyring is available the value is written to the keychain and any
    legacy plaintext QSettings copy is removed.
    """
    kr = _keyring()
    if kr is not None:
        try:
            if key:
                kr.set_password(SERVICE_NAME, KEY_NAME, key)
            else:
                # Empty key means "clear it".
                try:
                    kr.delete_password(SERVICE_NAME, KEY_NAME)
                except Exception:
                    pass
            # Never leave a plaintext copy behind.
            if settings is not None:
                settings.remove(KEY_NAME)
            return
        except Exception as e:
            logger.warning("Keychain write failed (%s); falling back to QSettings.", e)

    _warn_once()
    if settings is not None:
        settings.setValue(KEY_NAME, key)
