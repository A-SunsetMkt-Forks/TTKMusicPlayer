#include "musicleftareawidget.h"
#include "ui_musicapplication.h"
#include "musicapplication.h"
#include "musicleftitemlistuiobject.h"
#include "musicfunctionuiobject.h"
#include "musicdownloadmgmtwidget.h"
#include "musicdownloadrecordwidget.h"
#include "musicwebradioview.h"
#include "musicconnectlocalwidget.h"
#include "musiccloudsharedsongwidget.h"
#include "musicqualitychoicepopwidget.h"
#include "musicsongssummariziedwidget.h"
#include "musicrightareawidget.h"

MusicLeftAreaWidget *MusicLeftAreaWidget::m_instance = nullptr;

MusicLeftAreaWidget::MusicLeftAreaWidget(QWidget *parent)
    : QWidget(parent),
      m_currentIndex(0),
      m_stackedWidget(nullptr),
      m_localSharedSongWidget(nullptr),
      m_cloudSharedSongWidget(nullptr),
      m_qualityChoiceWidget(nullptr)
{
    m_instance = this;
}

MusicLeftAreaWidget::~MusicLeftAreaWidget()
{
    delete m_localSharedSongWidget;
    delete m_cloudSharedSongWidget;
    delete m_qualityChoiceWidget;
    delete m_stackedWidget;
}

MusicLeftAreaWidget *MusicLeftAreaWidget::instance()
{
    return m_instance;
}

void MusicLeftAreaWidget::setupUi(Ui::MusicApplication *ui)
{
    m_ui = ui;

    m_qualityChoiceWidget = new MusicQualityChoicePopWidget(this);
    m_ui->musicQualityWindow->addWidget(m_qualityChoiceWidget);
    m_ui->songsContainer->setLength(LEFT_SIDE_WIDTH_MIN, MusicAnimationStackedWidget::Module::LeftToRight);

    connect(ui->musicKey, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicStatePlay()));
    connect(ui->musicPrevious, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicPlayPrevious()));
    connect(ui->musicNext, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicPlayNext()));
    connect(ui->musicSound, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicVolumeMute()));
    connect(ui->musicSound, SIGNAL(musicVolumeChanged(int)), MusicApplication::instance(), SLOT(musicVolumeChanged(int)));
    connect(ui->musicBestLove, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicAddSongToLovestList()));
    connect(ui->musicDownload, SIGNAL(clicked()), this, SLOT(musicDownloadSongToLocal()));
    connect(ui->musicEnhancedButton, SIGNAL(enhancedMusicChanged(int)), MusicApplication::instance(), SLOT(musicEnhancedMusicChanged(int)));
    connect(ui->musicEnhancedButton, SIGNAL(enhancedMusicChanged(int)), ui->musicTimeWidget, SLOT(setSliderStyleByType(int)));
    connect(ui->userOptionWidget, SIGNAL(buttonClicked(int)), SLOT(switchToSelectedItemStyle(int)));

    ui->musicPrevious->setStyleSheet(MusicUIObject::BtnPrevious);
    ui->musicNext->setStyleSheet(MusicUIObject::BtnNext);
    ui->musicKey->setStyleSheet(MusicUIObject::BtnPlay);

    ui->musicBestLove->setStyleSheet(MusicUIObject::BtnUnLove);
    ui->musicDesktopLrc->setStyleSheet(MusicUIObject::BtnDKLrc);
    ui->musicDownload->setStyleSheet(MusicUIObject::BtnUnDownload);
    ui->musicMoreFunction->setStyleSheet(MusicUIObject::BtnMore);

    ui->musicPrevious->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicKey->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicNext->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicSound->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicBestLove->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicDesktopLrc->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicPlayMode->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicDownload->setCursor(QCursor(Qt::PointingHandCursor));
    ui->musicMoreFunction->setCursor(QCursor(Qt::PointingHandCursor));

    ui->windowClose->setToolTip(tr("Close"));
    ui->musicKey->setToolTip(tr("Play"));
    ui->musicPrevious->setToolTip(tr("Previous"));
    ui->musicNext->setToolTip(tr("Next"));
    ui->musicBestLove->setToolTip(tr("Best Love"));
    ui->musicDownload->setToolTip(tr("Download"));
    ui->musicMoreFunction->setToolTip(tr("More"));
    ui->musicDesktopLrc->setToolTip(tr("Show Desktop Lrc"));
    ui->musicPlayMode->setToolTip(tr("Play Mode"));
}

void MusicLeftAreaWidget::musictLoveStateClicked(bool state)
{
    m_ui->musicBestLove->setStyleSheet(state ? MusicUIObject::BtnLove : MusicUIObject::BtnUnLove);
    Q_EMIT currentLoveStateChanged();
}

void MusicLeftAreaWidget::musicDownloadSongToLocal()
{
    MusicDownloadMgmtWidget mgmt(this);
    mgmt.setSongName(m_ui->showCurrentSong->text(), MusicAbstractQueryRequest::QueryType::Music);
}

void MusicLeftAreaWidget::musicDownloadSongFinished()
{
    bool state = false;
    MusicApplication::instance()->musicDownloadContains(state);
    m_ui->musicDownload->setStyleSheet(state ? MusicUIObject::BtnDownload : MusicUIObject::BtnUnDownload);
    Q_EMIT currentDownloadStateChanged();
}

void MusicLeftAreaWidget::musicStackedSongListWidgetChanged()
{
    if(m_currentIndex == 0)
    {
        return;
    }

    delete m_stackedWidget;
    m_stackedWidget = nullptr;

    m_ui->songsContainer->setIndex(0, 0);
    m_ui->songsContainer->start(0);
    m_currentIndex = 0;
}

void MusicLeftAreaWidget::musicStackedLocalWidgetChanged()
{
    if(m_currentIndex == 1)
    {
        return;
    }

    delete m_stackedWidget;
    m_stackedWidget = new QWidget(this);
    m_stackedWidget->hide();

    if(m_cloudSharedSongWidget)
    {
        m_ui->songsContainer->removeWidget(m_cloudSharedSongWidget);
        m_cloudSharedSongWidget->hide();
    }

    if(!m_localSharedSongWidget)
    {
        m_localSharedSongWidget = new MusicConnectLocalWidget(this);
    }

    m_ui->songsContainer->addWidget(m_localSharedSongWidget);
    m_ui->songsContainer->setIndex(0, 0);
    m_ui->songsContainer->start(1);
    m_currentIndex = 1;
}

void MusicLeftAreaWidget::musicStackedCloudWidgetChanged()
{
    if(m_currentIndex == 2)
    {
        return;
    }

    delete m_stackedWidget;
    m_stackedWidget = new QWidget(this);
    m_stackedWidget->hide();

    if(m_localSharedSongWidget)
    {
        m_ui->songsContainer->removeWidget(m_localSharedSongWidget);
        m_localSharedSongWidget->hide();
    }

    if(!m_cloudSharedSongWidget)
    {
        m_cloudSharedSongWidget = new MusicCloudSharedSongWidget(this);
    }

    m_ui->songsContainer->addWidget(m_cloudSharedSongWidget);
    m_cloudSharedSongWidget->initialize();
    m_ui->songsContainer->setIndex(0, 0);
    m_ui->songsContainer->start(1);
    m_currentIndex = 2;
}

void MusicLeftAreaWidget::musicStackedRadioWidgetChanged()
{
    if(m_currentIndex == 3)
    {
        return;
    }

    delete m_stackedWidget;
    m_stackedWidget = new MusicWebRadioView(this);

    m_ui->songsContainer->insertWidget(1, m_stackedWidget);
    m_ui->songsContainer->setIndex(0, 0);
    m_ui->songsContainer->start(1);
    m_currentIndex = 3;
}

void MusicLeftAreaWidget::musicStackedMyDownWidgetChanged()
{
    if(m_currentIndex == 4)
    {
        return;
    }

    delete m_stackedWidget;
    m_stackedWidget = new MusicDownloadToolBoxWidget(this);

    m_ui->songsContainer->insertWidget(1, m_stackedWidget);
    m_ui->songsContainer->setIndex(0, 0);
    m_ui->songsContainer->start(1);
    m_currentIndex = 4;
}

void MusicLeftAreaWidget::switchToSelectedItemStyle(int index)
{
    switch(index)
    {
        case 0: musicStackedSongListWidgetChanged(); break;
        case 1: musicStackedLocalWidgetChanged(); break;
        case 2: musicStackedCloudWidgetChanged(); break;
        case 3: musicStackedRadioWidgetChanged(); break;
        case 4: musicStackedMyDownWidgetChanged(); break;
        default: break;
    }

    if(m_ui->musiclrccontainerforinterior->lrcDisplayExpand())
    {
        MusicRightAreaWidget::instance()->musicLrcDisplayAllButtonClicked();
    }
}
