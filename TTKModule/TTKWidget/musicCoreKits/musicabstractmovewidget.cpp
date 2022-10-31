#include "musicabstractmovewidget.h"
#include "musicbackgroundmanager.h"

#include <QBoxLayout>

MusicAbstractMoveWidget::MusicAbstractMoveWidget(QWidget *parent)
    : MusicAbstractMoveWidget(true, parent)
{

}

MusicAbstractMoveWidget::MusicAbstractMoveWidget(bool transparent, QWidget *parent)
    : TTKAbstractMoveWidget(transparent, parent),
      MusicWidgetRenderer()
{
    G_BACKGROUND_PTR->addObserver(this);
}

MusicAbstractMoveWidget::~MusicAbstractMoveWidget()
{
    G_BACKGROUND_PTR->removeObserver(this);
}

void MusicAbstractMoveWidget::backgroundChanged()
{
    setBackgroundPixmap(size());
}

void MusicAbstractMoveWidget::show()
{
    setBackgroundPixmap(size());
    QWidget::show();
}



MusicAbstractMoveSingleWidget::MusicAbstractMoveSingleWidget(QWidget *parent)
    : MusicAbstractMoveSingleWidget(true, parent)
{

}

MusicAbstractMoveSingleWidget::MusicAbstractMoveSingleWidget(bool transparent, QWidget *parent)
    : MusicAbstractMoveWidget(transparent, parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(0);

    m_container = new QWidget(this);
    layout->addWidget(m_container);
    setLayout(layout);
}

MusicAbstractMoveSingleWidget::~MusicAbstractMoveSingleWidget()
{
    delete m_container;
}
