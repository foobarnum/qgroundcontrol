/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @author Don Gagne <don@thegagnes.com>

#ifndef QGroundControlQmlGlobal_H
#define QGroundControlQmlGlobal_H

#include "QGCToolbox.h"
#include "QGCApplication.h"
#include "LinkManager.h"
#include "FlightMapSettings.h"
#include "SettingsFact.h"
#include "FactMetaData.h"
#include "SimulatedPosition.h"
#include "QGCLoggingCategory.h"

#ifdef QT_DEBUG
#include "MockLink.h"
#endif

class QGCToolbox;

class QGroundControlQmlGlobal : public QGCTool
{
    Q_OBJECT

public:
    QGroundControlQmlGlobal(QGCApplication* app);
    ~QGroundControlQmlGlobal();

    Q_PROPERTY(FlightMapSettings*   flightMapSettings   READ flightMapSettings      CONSTANT)
    Q_PROPERTY(LinkManager*         linkManager         READ linkManager            CONSTANT)
    Q_PROPERTY(MultiVehicleManager* multiVehicleManager READ multiVehicleManager    CONSTANT)
    Q_PROPERTY(QGCMapEngineManager* mapEngineManager    READ mapEngineManager       CONSTANT)
    Q_PROPERTY(QGCPositionManager*  qgcPositionManger   READ qgcPositionManger      CONSTANT)
    Q_PROPERTY(MissionCommandTree*  missionCommandTree  READ missionCommandTree     CONSTANT)
    Q_PROPERTY(VideoManager*        videoManager        READ videoManager           CONSTANT)
    Q_PROPERTY(MAVLinkLogManager*   mavlinkLogManager   READ mavlinkLogManager      CONSTANT)
    Q_PROPERTY(QGCCorePlugin*       corePlugin          READ corePlugin             CONSTANT)
    Q_PROPERTY(SettingsManager*     settingsManager     READ settingsManager        CONSTANT)

    Q_PROPERTY(int      supportedFirmwareCount          READ supportedFirmwareCount             CONSTANT)

    Q_PROPERTY(qreal                zOrderTopMost       READ zOrderTopMost          CONSTANT) ///< z order for top most items, toolbar, main window sub view
    Q_PROPERTY(qreal                zOrderWidgets       READ zOrderWidgets          CONSTANT) ///< z order value to widgets, for example: zoom controls, hud widgetss
    Q_PROPERTY(qreal                zOrderMapItems      READ zOrderMapItems         CONSTANT) ///< z order value for map items, for example: mission item indicators

    //-------------------------------------------------------------------------
    // MavLink Protocol
    Q_PROPERTY(bool     isVersionCheckEnabled   READ isVersionCheckEnabled      WRITE setIsVersionCheckEnabled      NOTIFY isVersionCheckEnabledChanged)
    Q_PROPERTY(int      mavlinkSystemID         READ mavlinkSystemID            WRITE setMavlinkSystemID            NOTIFY mavlinkSystemIDChanged)

    Q_PROPERTY(QGeoCoordinate lastKnownHomePosition READ lastKnownHomePosition  CONSTANT)
    Q_PROPERTY(QGeoCoordinate flightMapPosition     MEMBER _flightMapPosition   NOTIFY flightMapPositionChanged)
    Q_PROPERTY(double         flightMapZoom         MEMBER _flightMapZoom       NOTIFY flightMapZoomChanged)

    Q_PROPERTY(QString  parameterFileExtension  READ parameterFileExtension CONSTANT)
    Q_PROPERTY(QString  missionFileExtension    READ missionFileExtension   CONSTANT)
    Q_PROPERTY(QString  telemetryFileExtension  READ telemetryFileExtension CONSTANT)

    /// Returns the string for distance units which has configued by user
    Q_PROPERTY(QString appSettingsDistanceUnitsString READ appSettingsDistanceUnitsString CONSTANT)
    Q_PROPERTY(QString appSettingsAreaUnitsString READ appSettingsAreaUnitsString CONSTANT)

    Q_PROPERTY(QString qgcVersion READ qgcVersion CONSTANT)

    Q_PROPERTY(bool showTouchAreas MEMBER _showTouchAreas NOTIFY showTouchAreasChanged)
    Q_PROPERTY(bool showAdvancedUI MEMBER _showAdvancedUI NOTIFY showAdvancedUIChanged)

    Q_INVOKABLE void    saveGlobalSetting       (const QString& key, const QString& value);
    Q_INVOKABLE QString loadGlobalSetting       (const QString& key, const QString& defaultValue);
    Q_INVOKABLE void    saveBoolGlobalSetting   (const QString& key, bool value);
    Q_INVOKABLE bool    loadBoolGlobalSetting   (const QString& key, bool defaultValue);

    Q_INVOKABLE void    deleteAllSettingsNextBoot       () { _app->deleteAllSettingsNextBoot(); }
    Q_INVOKABLE void    clearDeleteAllSettingsNextBoot  () { _app->clearDeleteAllSettingsNextBoot(); }

    Q_INVOKABLE void    startPX4MockLink            (bool sendStatusText);
    Q_INVOKABLE void    startGenericMockLink        (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduCopterMockLink  (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduPlaneMockLink   (bool sendStatusText);
    Q_INVOKABLE void    startAPMArduSubMockLink     (bool sendStatusText);
    Q_INVOKABLE void    stopAllMockLinks            (void);

    /// Converts from meters to the user specified distance unit
    Q_INVOKABLE QVariant metersToAppSettingsDistanceUnits(const QVariant& meters) const { return FactMetaData::metersToAppSettingsDistanceUnits(meters); }

    /// Converts from user specified distance unit to meters
    Q_INVOKABLE QVariant appSettingsDistanceUnitsToMeters(const QVariant& distance) const { return FactMetaData::appSettingsDistanceUnitsToMeters(distance); }

    QString appSettingsDistanceUnitsString(void) const { return FactMetaData::appSettingsDistanceUnitsString(); }

    /// Converts from square meters to the user specified area unit
    Q_INVOKABLE QVariant squareMetersToAppSettingsAreaUnits(const QVariant& meters) const { return FactMetaData::squareMetersToAppSettingsAreaUnits(meters); }

    /// Converts from user specified area unit to square meters
    Q_INVOKABLE QVariant appSettingsAreaUnitsToSquareMeters(const QVariant& area) const { return FactMetaData::appSettingsAreaUnitsToSquareMeters(area); }

    QString appSettingsAreaUnitsString(void) const { return FactMetaData::appSettingsAreaUnitsString(); }

    /// Returns the list of available logging category names.
    Q_INVOKABLE QStringList loggingCategories(void) const { return QGCLoggingCategoryRegister::instance()->registeredCategories(); }

    /// Turns on/off logging for the specified category. State is saved in app settings.
    Q_INVOKABLE void setCategoryLoggingOn(const QString& category, bool enable) { QGCLoggingCategoryRegister::instance()->setCategoryLoggingOn(category, enable); }

    /// Returns true if logging is turned on for the specified category.
    Q_INVOKABLE bool categoryLoggingOn(const QString& category) { return QGCLoggingCategoryRegister::instance()->categoryLoggingOn(category); }

    /// Updates the logging filter rules after settings have changed
    Q_INVOKABLE void updateLoggingFilterRules(void) { QGCLoggingCategoryRegister::instance()->setFilterRulesFromSettings(QString()); }

    Q_INVOKABLE bool linesIntersect(QPointF xLine1, QPointF yLine1, QPointF xLine2, QPointF yLine2);

    Q_INVOKABLE QString urlToLocalFile(QUrl url) { return url.toLocalFile(); }

    // Property accesors

    FlightMapSettings*      flightMapSettings   ()  { return _flightMapSettings; }
    LinkManager*            linkManager         ()  { return _linkManager; }
    MultiVehicleManager*    multiVehicleManager ()  { return _multiVehicleManager; }
    QGCMapEngineManager*    mapEngineManager    ()  { return _mapEngineManager; }
    QGCPositionManager*     qgcPositionManger   ()  { return _qgcPositionManager; }
    MissionCommandTree*     missionCommandTree  ()  { return _missionCommandTree; }
    VideoManager*           videoManager        ()  { return _videoManager; }
    MAVLinkLogManager*      mavlinkLogManager   ()  { return _mavlinkLogManager; }
    QGCCorePlugin*          corePlugin          ()  { return _corePlugin; }
    SettingsManager*        settingsManager     ()  { return _settingsManager; }

    qreal                   zOrderTopMost       ()  { return 1000; }
    qreal                   zOrderWidgets       ()  { return 100; }
    qreal                   zOrderMapItems      ()  { return 50; }

    bool    isVersionCheckEnabled   () { return _toolbox->mavlinkProtocol()->versionCheckEnabled(); }
    int     mavlinkSystemID         () { return _toolbox->mavlinkProtocol()->getSystemId(); }

    QGeoCoordinate lastKnownHomePosition() { return qgcApp()->lastKnownHomePosition(); }

    int     supportedFirmwareCount      ();

    void    setIsVersionCheckEnabled    (bool enable);
    void    setMavlinkSystemID          (int  id);

    QString parameterFileExtension(void) const  { return QGCApplication::parameterFileExtension; }
    QString missionFileExtension(void) const    { return QGCApplication::missionFileExtension; }
    QString telemetryFileExtension(void) const  { return QGCApplication::telemetryFileExtension; }

    QString qgcVersion(void) const { return qgcApp()->applicationVersion(); }

    bool showTouchAreas(void) const { return _showTouchAreas; } ///< Show visible extents of touch areas
    bool showAdvancedUI(void) const { return _showAdvancedUI; } ///< Show hidden advanced UI

    // Overrides from QGCTool
    virtual void setToolbox(QGCToolbox* toolbox);

signals:
    void isMultiplexingEnabledChanged   (bool enabled);
    void isVersionCheckEnabledChanged   (bool enabled);
    void mavlinkSystemIDChanged         (int id);
    void flightMapPositionChanged       (QGeoCoordinate flightMapPosition);
    void flightMapZoomChanged           (double flightMapZoom);
    void showTouchAreasChanged          (bool showTouchAreas);
    void showAdvancedUIChanged          (bool showAdvancedUI);

private:
    FlightMapSettings*      _flightMapSettings;
    LinkManager*            _linkManager;
    MultiVehicleManager*    _multiVehicleManager;
    QGCMapEngineManager*    _mapEngineManager;
    QGCPositionManager*     _qgcPositionManager;
    MissionCommandTree*     _missionCommandTree;
    VideoManager*           _videoManager;
    MAVLinkLogManager*      _mavlinkLogManager;
    QGCCorePlugin*          _corePlugin;
    FirmwarePluginManager*  _firmwarePluginManager;
    SettingsManager*        _settingsManager;

    QGeoCoordinate          _flightMapPosition;
    double                  _flightMapZoom;

    bool                    _showTouchAreas;
    bool                    _showAdvancedUI;
};

#endif
