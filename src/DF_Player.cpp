#include "DF_Player.h"

HardwareSerial* DFPlayer::_serial = nullptr;
DFRobotDFPlayerMini DFPlayer::_player;

void DFPlayer::begin(uint8_t rxPin, uint8_t txPin, uint32_t baud)
{
    if (_serial == nullptr) {
        _serial = new HardwareSerial(DFPLAYER_UART_NUM);
    }

    _serial->begin(baud, SERIAL_8N1, rxPin, txPin);

    if (!_player.begin(*_serial, true)) {
        Serial.println("DFPlayer Mini not detected!");
    } else {
        _player.volume(DFPLAYER_VOLUME);
        Serial.println("DFPlayer Mini ready");
    }
}

void DFPlayer::play(uint16_t song)
{
    _player.play(song);
}

void DFPlayer::stop()
{
    _player.stop();
}

void DFPlayer::volume(uint8_t vol)
{
    if (vol > 30) vol = 30;
    _player.volume(vol);
}
