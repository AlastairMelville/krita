/*
 *  Copyright (c) 2018 Anna Medonosova <anna.medonosova@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KOGAMUTMASK_H
#define KOGAMUTMASK_H

#include <QPainter>
#include <QString>
#include <QVector>
#include <cmath>

#include <FlakeDebug.h>
#include <KoResource.h>
#include <KoShape.h>
#include <KoShapePaintingContext.h>

//class KoViewConverter;
class QTransform;

class KoGamutMaskShape
{
public:
    KoGamutMaskShape(KoShape* shape);
    KoGamutMaskShape();
    ~KoGamutMaskShape();

    bool coordIsClear(const QPointF& coord) const;
    QPainterPath outline();
    void paint(QPainter &painter);
    void paintStroke(QPainter &painter);
    KoShape* koShape();

private:
    KoShape* m_maskShape;
    KoShapePaintingContext m_shapePaintingContext;
};


/**
 * @brief The resource type for gamut masks used by the artistic color selector
 */
class KRITAFLAKE_EXPORT KoGamutMask : public QObject, public KoResource
{
    Q_OBJECT

public:
    KoGamutMask(const QString &filename);
    KoGamutMask();
    KoGamutMask(KoGamutMask *rhs);
    KoGamutMask(const KoGamutMask &rhs);
    KoGamutMask &operator=(const KoGamutMask &rhs) = delete;
    KoResourceSP clone() const override;
    ~KoGamutMask() override;

    bool coordIsClear(const QPointF& coord, bool preview);
    bool loadFromDevice(QIODevice *dev, KisResourcesInterfaceSP resourcesInterface) override;
    bool saveToDevice(QIODevice* dev) const override;

    QPair<QString, QString> resourceType() const override
    {
        return QPair<QString, QString>(ResourceType::GamutMasks, "");
    }

    void paint(QPainter &painter, bool preview);
    void paintStroke(QPainter &painter, bool preview);

    QTransform maskToViewTransform(quint8 viewSize);
    QTransform viewToMaskTransform(quint8 viewSize);

    QString title() const;
    void setTitle(QString title);

    QString description() const;
    void setDescription(QString description);

    QString defaultFileExtension() const override;

    int rotation();
    void setRotation(int rotation);

    QSizeF maskSize();

    void setMaskShapes(QList<KoShape*> shapes);   
    void setPreviewMaskShapes(QList<KoShape*> shapes);

    QList<KoShape*> koShapes() const;

    void clearPreview();

private:
    void setMaskShapesToVector(QList<KoShape*> shapes, QVector<KoGamutMaskShape*>& targetVector);

    struct Private;
    Private* const d;
};

typedef QSharedPointer<KoGamutMask> KoGamutMaskSP;

#endif // KOGAMUTMASK_H
