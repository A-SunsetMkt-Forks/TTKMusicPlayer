#include "sonicplugin.h"

#include <QSettings>

SonicPlugin *SonicPlugin::m_instance = nullptr;

SonicPlugin::SonicPlugin()
    : Effect()
{
    m_instance = this;
}

SonicPlugin::~SonicPlugin()
{
    if(m_stream)
    {
        sonicDestroyStream(m_stream);
    }
}

void SonicPlugin::applyEffect(Buffer *b)
{
    sonicWriteFloatToStream(m_stream, b->data, b->samples);
    const int samples = sonicSamplesAvailable(m_stream);

    if(samples > b->size)
    {
        delete[] b->data;
        b->size = ceil(samples * 1.0 / b->size) * QMMP_BLOCK_FRAMES * channels();
        b->data = new float[b->size];
        b->samples = b->size;
    }

    int samplesWritten = 0;
    float buffer[b->size * 2] = {0};

    do
    {
        samplesWritten = sonicReadFloatFromStream(m_stream, buffer, b->size);
        if(samplesWritten > 0)
        {
          memcpy(b->data, buffer, samplesWritten * sizeof(float));
          b->samples = samplesWritten;
      }
    } while(samplesWritten > 0);
}

void SonicPlugin::configure(quint32 srate, ChannelMap map)
{
    Effect::configure(srate, map);

    m_stream = sonicCreateStream(srate, map.count());
    sonicSetVolume(m_stream, 1);
    sonicSetQuality(m_stream, 0);

    QSettings settings(Qmmp::configFile(), QSettings::IniFormat);
    setRatio(settings.value("Sonic/ratio", DEFAULT_RATIO).toInt());
}

void SonicPlugin::setRatio(int ratio)
{
    sonicSetRate(m_stream, ratio * 1.0 / DEFAULT_RATIO);
}

SonicPlugin* SonicPlugin::instance()
{
    return m_instance;
}
