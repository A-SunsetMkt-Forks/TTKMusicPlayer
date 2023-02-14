#include "musicformats.h"

#include <qmmp/format.h>

bool MusicFormats::songTrackValid(const QString &url)
{
    return Format::songTrackValid(url);
}

QStringList MusicFormats::supportMusicFormats()
{
    return Format::supportMusicFormats();
}

QStringList MusicFormats::supportMusicInputFilterFormats()
{
    return Format::supportMusicInputFilterFormats();
}

QString MusicFormats::supportMusicInputFormats()
{
    const QStringList formats(Format::supportMusicInputFormats());
    return formats.join(";;");
}

QStringList MusicFormats::supportSpekInputFilterFormats()
{
    QStringList formats;
    formats << "*.wma" << "*.ape" << "*.tta" << "*.m4a" << "*.m4b" << "*.aac" << "*.ra" << "*.shn" << "*.ac3" << "*.mka" << "*.vqf" << "*.tak" << "*.spx" << "*.adx" << "*.aix";
    formats << "*.wve" << "*.sln" << "*.paf" << "*.pvf" << "*.ircam" << "*.gsm" << "*.avr" << "*.amr" << "*.dsf" << "*.dsdiff";
    formats << "*.webm" << "*.3g2" << "*.3gp" << "*.asf" << "*.avi" << "*.f4v" << "*.flv" << "*.hevc" << "*.m4v" << "*.mov" << "*.mp4" << "*.mpeg" << "*.rm" << "*.swf" << "*.vob" << "*.wtv";
    formats << "*.aiff" << "*.au" << "*.dts" << "*.mp3" << "*.ogg" << "*.opus" << "*.snd" << "*.oga" << "*.flac";
    return formats;
}

QString MusicFormats::supportSpekInputFormats()
{
    return QString("Audio Files (%1)").arg(supportSpekInputFilterFormats().join(" "));
}

QString MusicFormats::supportPlaylistInputFormats()
{
    QStringList formats;
    formats << "Playlist Files (*.tkpl *.m3u *.m3u8 *.pls *.wpl *.xspf *.jspf *.asx *.fpl *.dbpl *.csv *.txt)";
    formats << "TTKlist Files (*.tkpl)";
    formats << "M3U Files (*.m3u)";
    formats << "M3U8 Files (*.m3u8)";
    formats << "Playlist Files (*.pls)";
    formats << "Windows Playlist Files (*.wpl)";
    formats << "XML Shareable Playlist Files (*.xspf)";
    formats << "JSON Shareable Playlist Files (*.jspf)";
    formats << "Windows Media Playlist Files (*.asx)";
    formats << "Foobar2k Playlist Files (*.fpl)";
    formats << "Deadbeef Playlist Files (*.dbpl)";
    formats << "CSV Playlist Files (*.csv)";
    formats << "TXT Playlist Files (*.txt)";
    return formats.join(";;");
}

QString MusicFormats::supportPlaylistOutputFormats()
{
    QStringList formats;
    formats << "TTKlist Files (*.tkpl)";
    formats << "M3U Files (*.m3u)";
    formats << "M3U8 Files (*.m3u8)";
    formats << "Playlist Files (*.pls)";
    formats << "Windows Playlist Files (*.wpl)";
    formats << "XML Shareable Playlist Files (*.xspf)";
    formats << "JSON Shareable Playlist Files (*.jspf)";
    formats << "Windows Media Playlist Files (*.asx)";
    formats << "CSV Playlist Files (*.csv)";
    formats << "TXT Playlist Files (*.txt)";
    return formats.join(";;");
}
