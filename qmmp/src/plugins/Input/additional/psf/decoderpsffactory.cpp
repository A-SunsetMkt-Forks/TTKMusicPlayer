#include "psfhelper.h"
#include "decoder_psf.h"
#include "decoderpsffactory.h"
#include "psfmetadatamodel.h"

bool DecoderPSFFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderPSFFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("PSF Plugin");
    properties.filters << "*.psf" << "*.psf2";
    properties.filters << "*.spu";
    properties.filters << "*.ssf";
    properties.filters << "*.qsf";
    properties.filters << "*.dsf";
    properties.filters << "*.minipsf" << "*.minipsf2" << "*.minissf" << "*.miniqsf" << "*.minidsf";
    properties.description = tr("Audio Overload Files");
    properties.shortName = "psf";
    properties.noInput = true;
    properties.protocols << "psf";
    return properties;
}

Decoder *DecoderPSFFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderPSF(path);
}

QList<TrackInfo*> DecoderPSFFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);

    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    PSFHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::MetaData)
    {
        helper.readMetaTags();
        info->setValue(Qmmp::TITLE, helper.title());
        info->setValue(Qmmp::ARTIST, helper.artist());
        info->setValue(Qmmp::ALBUM, helper.album());
        info->setValue(Qmmp::YEAR, helper.year());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.bitsPerSample());
        info->setValue(Qmmp::FORMAT_NAME, "PSF");
        info->setDuration(helper.totalTime());
    }

    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderPSFFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(readOnly);
    return new PSFMetaDataModel(path);
}

#ifndef QMMP_GREATER_NEW
#include <QtPlugin>
Q_EXPORT_PLUGIN2(psf, DecoderPSFFactory)
#endif
