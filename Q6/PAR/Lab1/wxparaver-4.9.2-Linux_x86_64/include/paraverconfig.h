/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                               libparaver-api                              *
 *                      API Library for libparaver-kernel                    *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 2.1      *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/


#ifndef PARAVERCONFIG_H_INCLUDED
#define PARAVERCONFIG_H_INCLUDED

#include <map>
#include <sstream>

#include "paraverkerneltypes.h"
#include "drawmode.h"
#include "semanticcolor.h"
#include "paravertypes.h"
#include "window.h"

// SERIALIZATION INCLUDES
#include <fstream>
#include <iostream>
#include <boost/serialization/string.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>


class ParaverConfig;

class PropertyFunction
{
  public:
    PropertyFunction()
    {}
    virtual ~PropertyFunction()
    {}
    virtual void parseLine( std::istringstream& line, ParaverConfig& config ) = 0;
};

class ParaverConfig
{
  public:

    enum TImageFormat
    {
      BMP = 0,
      JPG,
      PNG,
      XPM
    };

    enum TTextFormat // << also matrix-row format
    {
      CSV = 0,
      GNUPLOT,
      PLAIN
    };

    ParaverConfig();
    ~ParaverConfig();

    static ParaverConfig *getInstance();

    void readParaverConfigFile();
    static void writeParaverConfigFile( bool writeBackup = true );
    static bool writeDefaultConfig();

    std::string getParaverConfigDir();


    bool initCompleteSessionFile();
    void cleanCompleteSessionFile();
    bool closeCompleteSessionFile();

    // GLOBAL XML SECTION
    void setGlobalTracesPath( std::string whichTracesPath );
    void setGlobalCFGsPath( std::string whichCfgsPath );
    void setGlobalXMLsPath( std::string whichXMLsPath );
    void setGlobalTutorialsPath( std::string whichTutorialsPath );
    void setGlobalTmpPath( std::string whichTmpPath );
    void setGlobalApplyFollowingCFGsToAllTraces( bool whichApplyFollowingCFGsToAllTraces );
    void setGlobalFillStateGaps( bool whichFillStateGaps );
    void setGlobalFullTracePath( bool whichFullTracePath );
    void setGlobalSingleInstance( bool whichSingleInstance );
    void setMainWindowWidth( unsigned int whichWidth );
    void setMainWindowHeight( unsigned int whichHeight );
    void setGlobalSessionPath( std::string whichSessionPath );
    void setGlobalSessionSaveTime( PRV_UINT16 whichSessionSaveTime );
    void setGlobalPrevSessionLoad( bool isPrevSessionLoaded );
    void setGlobalHelpContentsUsesBrowser( bool isHelpContentsUsesBrowser );
    void setGlobalHelpContentsQuestionAnswered( bool isHelpContentsQuestionAnswered );
    void setAppsChecked(); // will always set to True
    void setDisableTimelineZoomMouseWheel( bool disable );


    std::string getGlobalTracesPath() const;
    std::string getGlobalCFGsPath() const;
    std::string getGlobalXMLsPath() const;
    std::string getGlobalTutorialsPath() const;
    std::string getGlobalTmpPath() const;
    bool getGlobalApplyFollowingCFGsToAllTraces() const;
    bool getGlobalFillStateGaps() const;
    bool getGlobalFullTracePath() const;
    bool getGlobalSingleInstance() const;
    unsigned int getMainWindowWidth() const;
    unsigned int getMainWindowHeight() const;
    std::string getGlobalSessionPath() const;
    PRV_UINT16 getGlobalSessionSaveTime() const;
    bool getGlobalPrevSessionLoad() const;
    bool getGlobalHelpContentsUsesBrowser() const;
    bool getGlobalHelpContentsQuestionAnswered() const;
    bool getDisableTimelineZoomMouseWheel() const;

    bool getAppsChecked() const;

    // TIMELINES XML SECTION
    void setTimelineDefaultName( std::string whichDefaultName );
    void setTimelineNameFormat( std::string whichNameFormat );
    void setTimelineDefaultCFG( std::string whichDefaultCFG );
    void setTimelinePrecision( PRV_UINT32 whichPrecision );
    void setTimelineViewEventsLines( bool whichViewEventLines );
    void setTimelineViewCommunicationsLines( bool whichViewCommunicationsLines );
    void setTimelineViewFunctionAsColor( bool whichViewFunctionAsColor );
    void setTimelineColor( SemanticColor::TColorFunction whichColor );
    void setTimelineDrawmodeTime( DrawModeMethod whichDrawmodeTime );
    void setTimelineDrawmodeObjects( DrawModeMethod whichDrawmodeObjects );
    void setTimelineGradientFunction( GradientColor::TGradientFunction whichGradientFunction );
    void setTimelineSemanticScaleMinAtZero( bool whichMinAtZero );
    void setTimelinePixelSize( PRV_UINT32 whichPixelSize );
    void setTimelineLabels( Window::TObjectLabels whichLabels );
    void setTimelineObjectAxisSize( Window::TObjectAxisSize whichSize );
    void setTimelineWhatWhereSemantic( bool whichWhatWhereSemantic );
    void setTimelineWhatWhereEvents( bool whichWhatWhereEvents );
    void setTimelineWhatWhereCommunications( bool whichWhatWhereCommunications );
    void setTimelineWhatWherePreviousNext( bool whichWhatWherePreviousNext );
    void setTimelineWhatWhereText( bool whichWhatWhereText );
    void setTimelineWhatWhereEventPixels( PRV_INT16 eventPixels );
    void setTimelineSaveTextFormat( TTextFormat whichSaveTextFormat );
    void setTimelineSaveImageFormat( TImageFormat whichSaveImageFormat );

    std::string getTimelineDefaultName() const;
    std::string getTimelineNameFormat() const;
    std::string getTimelineDefaultCFG() const;
    PRV_UINT32 getTimelinePrecision() const;
    bool getTimelineViewEventsLines() const;
    bool getTimelineViewCommunicationsLines() const;
    bool getTimelineViewFunctionAsColor() const;
    SemanticColor::TColorFunction getTimelineColor() const;
    DrawModeMethod getTimelineDrawmodeTime() const;
    DrawModeMethod getTimelineDrawmodeObjects() const;
    GradientColor::TGradientFunction getTimelineGradientFunction() const;
    bool getTimelineSemanticScaleMinAtZero() const;
    PRV_UINT32 getTimelinePixelSize() const;
    Window::TObjectLabels getTimelineLabels() const;
    Window::TObjectAxisSize getTimelineObjectAxisSize() const;
    bool getTimelineWhatWhereSemantic() const;
    bool getTimelineWhatWhereEvents() const;
    bool getTimelineWhatWhereCommunications() const;
    bool getTimelineWhatWherePreviousNext() const;
    bool getTimelineWhatWhereText() const;
    PRV_INT16 getTimelineWhatWhereEventPixels() const;
    TTextFormat getTimelineSaveTextFormat() const;
    TImageFormat getTimelineSaveImageFormat() const;

    // HISTOGRAM
    void setHistogramViewZoom( bool whichViewZoom );
    void setHistogramViewFirstRowColored( bool whichViewFirstRow );
    void setHistogramViewGradientColors( bool whichViewGradientColors );
    void setHistogramViewHorizontal( bool whichViewHorizontal );
    void setHistogramViewEmptyColumns( bool whichViewEmptyColumns );
    void setHistogramScientificNotation( bool whichScientificNotation );
    void setHistogramThousandSep( bool whichThousandSep );
    void setHistogramPrecision( PRV_UINT32 whichPrecision );
    void setHistogramShowUnits( bool whichShowUnits );
    void setHistogramNumColumns( TObjectOrder whichNumColumns );
    void setHistogramAutofitControlScale( bool whichAutofitControlScale );
    void setHistogramAutofitControlScaleZero( bool whichAutofitControlScaleZero );
    void setHistogramAutofitDataGradient( bool whichAutofitDataGradient );
    void setHistogramAutofitThirdDimensionScale( bool whichAutofitThirdDimensionScale );
    void setHistogramGradientFunction( GradientColor::TGradientFunction whichGradientFunction );
    void setHistogramDrawmodeSemantic( DrawModeMethod whichDrawmodeSemantic );
    void setHistogramDrawmodeObjects( DrawModeMethod whichDrawmodeObjects );
    void setHistogramSaveTextAsMatrix( bool whichSaveTextAsMatrix );
    void setHistogramSaveTextFormat( TTextFormat whichSaveTextFormat );
    void setHistogramSaveImageFormat( TImageFormat whichSaveImageFormat );
    void setHistogramPixelSize( PRV_UINT16 whichPixelSize );
    void setHistogramSkipCreateDialog( bool whichSkipCreateDialog );
    void setHistogramOnlyTotals( bool whichOnlyTotals );
    void setHistogramShortLabels( bool whichShortLabels );

    bool getHistogramViewZoom() const;
    bool getHistogramViewFirstRowColored() const;
    bool getHistogramViewGradientColors() const;
    bool getHistogramViewHorizontal() const;
    bool getHistogramViewEmptyColumns() const;
    bool getHistogramScientificNotation() const;
    bool getHistogramThousandSep() const;
    PRV_UINT32 getHistogramPrecision() const;
    bool getHistogramShowUnits() const;
    TObjectOrder getHistogramNumColumns() const;
    bool getHistogramAutofitControlScale() const;
    bool getHistogramAutofitControlScaleZero() const;
    bool getHistogramAutofitDataGradient() const;
    bool getHistogramAutofitThirdDimensionScale() const;
    GradientColor::TGradientFunction getHistogramGradientFunction() const;
    DrawModeMethod getHistogramDrawmodeSemantic() const;
    DrawModeMethod getHistogramDrawmodeObjects() const;
    bool getHistogramSaveTextAsMatrix() const;
    TTextFormat getHistogramSaveTextFormat() const;
    TImageFormat getHistogramSaveImageFormat() const;
    PRV_UINT16 getHistogramPixelSize() const;
    bool getHistogramSkipCreateDialog() const;
    bool getHistogramOnlyTotals() const;
    bool getHistogramShortLabels() const;


    // FILTERS XML SECTION : GLOBAL
    void setFiltersFilterTraceUpToMB( float whichFilterTraceUpToMB );
    void setFiltersXMLPath( std::string whichXMLPath );

    float getFiltersFilterTraceUpToMB() const;
    std::string getFiltersXMLPath() const;

    // FILTERS XML SECTION : Cutter
    void setCutterByTime( bool whichByTime );
    void setCutterMinimumTime( TTime minTime );
    void setCutterMaximumTime( TTime maxTime );
    void setCutterMinimumTimePercentage( TTime minTimePercentage );
    void setCutterMaximumTimePercentage( TTime maxTimePercentage );

    void setCutterOriginalTime( bool originalTime );
    // void setFiltersTasksList(  );
    void setCutterBreakStates( bool breakStates );
    void setCutterRemoveFirstStates( bool removeFirstStates );
    void setCutterRemoveLastStates( bool removeLastStates );
    void setCutterKeepEvents( bool keepEvents );

    bool getCutterByTime();
    TTime getCutterMinimumTime();
    TTime getCutterMaximumTime();
    TTime getCutterMinimumTimePercentage();
    TTime getCutterMaximumTimePercentage();
    bool getCutterOriginalTime();
    //  setFiltersTasksList(  );
    bool getCutterBreakStates();
    bool getCutterRemoveFirstStates();
    bool getCutterRemoveLastStates();
    bool getCutterKeepEvents();

    // FILTERS XML SECTION : FILTER
    void setFilterDiscardStates( bool discard );
    void setFilterDiscardEvents( bool discard );
    void setFilterDiscardCommunications( bool discard );
    void setFilterCommunicationsMinimumSize( TCommSize size );
    bool getFilterDiscardStates();
    bool getFilterDiscardEvents();
    bool getFilterDiscardCommunications();
    TCommSize getFilterCommunicationsMinimumSize();

    // FILTERS XML SECTION : SOFTWARE COUNTERS
    void setSoftwareCountersInvervalsOrStates( bool whichIntervalsOrStates );
    void setSoftwareCountersSamplingInterval( TTime whichSamplingInterval );
    void setSoftwareCountersMinimumBurstTime( TTime whichMinimumBurstTime );
    void setSoftwareCountersTypes( std::string whichTypes );
    void setSoftwareCountersCountEventsOrAcummulateValues( bool whichCountEventsOrAcummulateValues );
    void setSoftwareCountersRemoveStates( bool whichRemoveStates );
    void setSoftwareCountersSummarizeStates( bool whichSummarizeStates );
    void setSoftwareCountersGlobalCounters( bool whichGlobalCounters );
    void setSoftwareCountersOnlyInBursts( bool whichOnlyInBursts );
    void setSoftwareCountersTypesKept( std::string whichTypesKept );

    bool getSoftwareCountersInvervalsOrStates();
    TTime getSoftwareCountersSamplingInterval();
    TTime getSoftwareCountersMinimumBurstTime();
    std::string getSoftwareCountersTypes();
    bool getSoftwareCountersCountEventsOrAcummulateValues();
    bool getSoftwareCountersRemoveStates();
    bool getSoftwareCountersSummarizeStates();
    bool getSoftwareCountersGlobalCounters();
    bool getSoftwareCountersOnlyInBursts();
    std::string getSoftwareCountersTypesKept();

    // COLORS XML SECTION    std::string getParaverConfigDir();

    void setColorsTimelineBackground( rgb whichTimelineBackground );
    void setColorsTimelineAxis( rgb whichTimelineAxis );
    void setColorsTimelineZeroDashLine( rgb whichTimelineZeroDashLine );
    void setColorsTimelineUseZero( bool useZero );
    void setColorsTimelineColorZero( rgb whichTimelineZero );
    void setColorsTimelinePunctual( rgb whichPunctual );
    void setColorsTimelineLogicalCommunications( rgb whichTimelineLogicalCommunications );
    void setColorsTimelinePhysicalCommunications( rgb whichTimelinePhysicalCommunications );
    void setColorsTopGradient( rgb whichTopGradient );
    void setColorsLowGradient( rgb whichLowGradient );
    void setColorsBeginGradient( rgb whichBeginGradient );
    void setColorsEndGradient( rgb whichEndGradient );
    void setColorsBeginNegativeGradient( rgb whichBeginGradient );
    void setColorsEndNegativeGradient( rgb whichEndGradient );

    rgb getColorsTimelineBackground() const;
    rgb getColorsTimelineAxis() const;
    rgb getColorsTimelineZeroDashLine() const;
    bool getColorsTimelineUseZero() const;
    rgb getColorsTimelineColorZero() const;
    rgb getColorsTimelinePunctual() const;
    rgb getColorsTimelineLogicalCommunications() const;
    rgb getColorsTimelinePhysicalCommunications() const;
    rgb getColorsTopGradient() const;
    rgb getColorsLowGradient() const;
    rgb getColorsBeginGradient() const;
    rgb getColorsEndGradient() const;
    rgb getColorsBeginNegativeGradient() const;
    rgb getColorsEndNegativeGradient() const;

    // EXTERNAL APPLICATIONS
    void setGlobalExternalTextEditors( std::vector< std::string> whichTextEditors );
    void setGlobalExternalPDFReaders( std::vector< std::string> whichPDFReaders );

    std::vector< std::string> getGlobalExternalTextEditors() const;
    std::vector< std::string> getGlobalExternalPDFReaders() const;


    void saveXML( const std::string &filename );
    void loadXML( const std::string &filename );

  private:
    friend class boost::serialization::access;

    static ParaverConfig *instance;
    std::map<std::string, PropertyFunction *> propertyFunctions;

    std::string paraverConfigDir;
    bool isModified;

    void loadMap();
    void unloadMap();

    struct XMLPreferencesGlobal
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "traces_path", tracesPath );
        ar & boost::serialization::make_nvp( "cfgs_path", cfgsPath );
        ar & boost::serialization::make_nvp( "tmp_path", tmpPath );
        if ( version >= 4 )
        {
          ar & boost::serialization::make_nvp( "tutorials_path", tutorialsPath );
        }
        // ar & boost::serialization::make_nvp( "apply_following_cfgs_to_all_traces", applyFollowingCFGsToAllTraces );
        ar & boost::serialization::make_nvp( "fill_state_gaps", fillStateGaps );
        if( version >= 5 )
          ar & boost::serialization::make_nvp( "full_trace_path", fullTracePath );
        if( version >= 1 )
          ar & boost::serialization::make_nvp( "single_instance", singleInstance );
        if( version >= 2 )
        {
          ar & boost::serialization::make_nvp( "main_window_width", mainWindowWidth );
          ar & boost::serialization::make_nvp( "main_window_height", mainWindowHeight );
        }
        if( version >= 3 )
        {
          ar & boost::serialization::make_nvp( "session_path", sessionPath );
          ar & boost::serialization::make_nvp( "session_save_time", sessionSaveTime );
        }
        if( version >= 6 )
        {
          ar & boost::serialization::make_nvp( "prev_session_load", prevSessionLoad );
        }
        if( version >= 7 )
        {
          ar & boost::serialization::make_nvp( "help_contents_browser", helpContentsUsesBrowser );
          ar & boost::serialization::make_nvp( "help_contents_question", helpContentsQuestionAnswered );
        }
        if ( version >= 8 )
        {
          ar & boost::serialization::make_nvp( "apps_checked", appsChecked );
        }
        if ( version >= 9 )
        {
          ar & boost::serialization::make_nvp( "disable_timeline_zoom_mouse_wheel", disableTimelineZoomMouseWheel );
        }
      }

      std::string tracesPath; // also for paraload.sig!
      std::string cfgsPath;
      std::string tutorialsPath;
      std::string tmpPath;    // errors, logs, working dir
      bool applyFollowingCFGsToAllTraces;
      bool fillStateGaps;
      bool fullTracePath;
      bool singleInstance;
      unsigned int mainWindowWidth;
      unsigned int mainWindowHeight;
      std::string sessionPath;
      PRV_UINT16 sessionSaveTime;
      bool prevSessionLoad;
      bool helpContentsUsesBrowser;
      bool helpContentsQuestionAnswered;
      bool disableTimelineZoomMouseWheel;
      bool appsChecked;

    } xmlGlobal;


    struct XMLPreferencesTimeline
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "default_name", defaultName );
        ar & boost::serialization::make_nvp( "name_format", nameFormat );
        ar & boost::serialization::make_nvp( "default_applied_cfg", defaultCFG );
        ar & boost::serialization::make_nvp( "decimal_precision", precision );
        ar & boost::serialization::make_nvp( "view_events_lines", viewEventsLines );
        ar & boost::serialization::make_nvp( "view_communications_lines", viewCommunicationsLines );
        //DEPRECATED
        ar & boost::serialization::make_nvp( "view_function_as_color", viewFunctionAsColor );
        ar & boost::serialization::make_nvp( "color", color );
        ar & boost::serialization::make_nvp( "drawmode_time", drawmodeTime );
        ar & boost::serialization::make_nvp( "drawmode_objects", drawmodeObjects );
        ar & boost::serialization::make_nvp( "gradient_function", gradientFunction );
        ar & boost::serialization::make_nvp( "pixel_size", pixelSize );
        ar & boost::serialization::make_nvp( "what_where_semantic", whatWhereSemantic );
        ar & boost::serialization::make_nvp( "what_where_events", whatWhereEvents );
        ar & boost::serialization::make_nvp( "what_where_communications", whatWhereCommunications );
        ar & boost::serialization::make_nvp( "what_where_previous_next", whatWherePreviousNext );
        ar & boost::serialization::make_nvp( "what_where_text", whatWhereText );
        ar & boost::serialization::make_nvp( "save_text_format", saveTextFormat );
        ar & boost::serialization::make_nvp( "save_image_format", saveImageFormat );
        if( version >= 1 )
          ar & boost::serialization::make_nvp( "what_where_event_pixels", whatWhereEventPixels );
        if( version >= 2 )
          ar & boost::serialization::make_nvp( "object_labels", objectLabels );
        if( version >= 3 )
          ar & boost::serialization::make_nvp( "object_axis_size", objectAxisSize );
        if ( version >= 4 )
          ar & boost::serialization::make_nvp( "semantic_scale_min_at_zero", semanticScaleMinAtZero );
      }

      std::string defaultName;
      std::string nameFormat;
      std::string defaultCFG;
      PRV_UINT32 precision;
      bool viewEventsLines;
      bool viewCommunicationsLines;
      //DEPRECATED
      bool viewFunctionAsColor;
      SemanticColor::TColorFunction color;
      DrawModeMethod drawmodeTime;
      DrawModeMethod drawmodeObjects;
      GradientColor::TGradientFunction gradientFunction;
      bool semanticScaleMinAtZero;
      PRV_UINT32 pixelSize;
      Window::TObjectLabels objectLabels;
      Window::TObjectAxisSize objectAxisSize;
      bool whatWhereSemantic;
      bool whatWhereEvents;
      bool whatWhereCommunications;
      bool whatWherePreviousNext;
      bool whatWhereText;
      PRV_UINT16 whatWhereEventPixels;
      TTextFormat saveTextFormat;
      TImageFormat saveImageFormat;

    } xmlTimeline;

    struct XMLPreferencesHistogram
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "view_zoom", viewZoom );
        ar & boost::serialization::make_nvp( "view_gradient_colors", viewGradientColors );
        ar & boost::serialization::make_nvp( "view_horizontal", viewHorizontal );
        ar & boost::serialization::make_nvp( "view_empty_columns", viewEmptyColumns );
        ar & boost::serialization::make_nvp( "cell_scientific_notation", scientificNotation );
        ar & boost::serialization::make_nvp( "cell_thousands_separator", thousandSep );
        ar & boost::serialization::make_nvp( "cell_decimal_precision", precision );
        ar & boost::serialization::make_nvp( "cell_show_units", showUnits );
        ar & boost::serialization::make_nvp( "number_of_columns", histoNumColumns );
        ar & boost::serialization::make_nvp( "autofit_control_scale", autofitControlScale );
        ar & boost::serialization::make_nvp( "autofit_data_gradient", autofitDataGradient );
        ar & boost::serialization::make_nvp( "autofit_third_dimension_scale", autofitThirdDimensionScale );
        ar & boost::serialization::make_nvp( "gradient_function", gradientFunction );
        ar & boost::serialization::make_nvp( "drawmode_semantic", drawmodeSemantic );
        ar & boost::serialization::make_nvp( "drawmode_objects", drawmodeObjects );
        ar & boost::serialization::make_nvp( "save_text_as_matrix", saveTextAsMatrix );
        ar & boost::serialization::make_nvp( "save_text_format", saveTextFormat );
        ar & boost::serialization::make_nvp( "save_image_format", saveImageFormat );
        if( version >= 1 )
          ar & boost::serialization::make_nvp( "view_first_row_colored", viewFirstRowColored );
        if( version >= 3 )
          ar & boost::serialization::make_nvp( "pixel_size_histogram", pixelSize );
        if( version >= 4 )
          ar & boost::serialization::make_nvp( "skip_create_dialog", skipCreateDialog );
        if( version >= 5 )
          ar & boost::serialization::make_nvp( "show_only_totals", onlyTotals );
        if( version >= 6 )
          ar & boost::serialization::make_nvp( "column_short_labels", shortLabels );
        if( version >= 7 )
          ar & boost::serialization::make_nvp( "autofit_control_scale_zero", autofitControlScaleZero );
      }

      bool viewZoom;
      bool viewFirstRowColored;
      bool viewGradientColors;
      bool viewHorizontal;
      bool viewEmptyColumns;
      bool scientificNotation;
      bool thousandSep;
      PRV_UINT32 precision;
      bool showUnits;
      TObjectOrder histoNumColumns;
      bool autofitControlScale;
      bool autofitControlScaleZero;
      bool autofitDataGradient;
      bool autofitThirdDimensionScale;
      GradientColor::TGradientFunction gradientFunction;
      DrawModeMethod drawmodeSemantic;
      DrawModeMethod drawmodeObjects;
      bool saveTextAsMatrix;
      TTextFormat saveTextFormat;
      TImageFormat saveImageFormat;
      PRV_UINT16 pixelSize;
      bool skipCreateDialog;
      bool onlyTotals;
      bool shortLabels;

    } xmlHistogram;


    struct XMLPreferencesCutter
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "by_time", byTime );
        ar & boost::serialization::make_nvp( "minimum_time", minimumTime );
        ar & boost::serialization::make_nvp( "maximum_time", maximumTime );
        ar & boost::serialization::make_nvp( "minimum_time_percentage", minimumTimePercentage );
        ar & boost::serialization::make_nvp( "maximum_time_percentage", maximumTimePercentage );
        ar & boost::serialization::make_nvp( "original_time", originalTime );
        ar & boost::serialization::make_nvp( "break_states", breakStates );
        ar & boost::serialization::make_nvp( "remove_first_states", removeFirstStates );
        ar & boost::serialization::make_nvp( "remove_last_states", removeLastStates );
        if( version >= 1 )
          ar & boost::serialization::make_nvp( "keep_events", keepEvents );
      }

      bool byTime;
      TTime minimumTime;
      TTime maximumTime;
      TTime minimumTimePercentage;
      TTime maximumTimePercentage;
      bool originalTime;
      bool breakStates;
      bool removeFirstStates;
      bool removeLastStates;
      bool keepEvents;

    };


    struct XMLPreferencesFilter
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "discard_states", discardStates );
        ar & boost::serialization::make_nvp( "discard_events", discardEvents );
        ar & boost::serialization::make_nvp( "discard_communications", discardCommunications );
        ar & boost::serialization::make_nvp( "comms", communicationsMinimumSize );
      }

      bool discardStates;
      bool discardEvents;
      bool discardCommunications;
      TCommSize communicationsMinimumSize;

    };

    struct XMLPreferencesSoftwareCountersRange
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "by_intervals_vs_by_states", intervalsOrStates );
        ar & boost::serialization::make_nvp( "sampling_inteval", samplingInterval );
        ar & boost::serialization::make_nvp( "minimum_burst_time", minimumBurstTime );
        ar & boost::serialization::make_nvp( "events", types );
      }

      bool intervalsOrStates;
      TTime samplingInterval;
      TTime minimumBurstTime;
      std::string types;

    };

    struct XMLPreferencesSoftwareCountersAlgorithm
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "count_events_vs_acummulate_values", countEventsOrAcummulateValues );
        ar & boost::serialization::make_nvp( "remove_states", removeStates );
        ar & boost::serialization::make_nvp( "summarize_useful_states", summarizeStates );
        ar & boost::serialization::make_nvp( "global_counters", globalCounters );
        ar & boost::serialization::make_nvp( "only_in_burst_counting", onlyInBursts );
        ar & boost::serialization::make_nvp( "keep_events", typesKept );
      }

      bool countEventsOrAcummulateValues;
      bool removeStates;
      bool summarizeStates;
      bool globalCounters;
      bool onlyInBursts;
      std::string typesKept;

    };

    struct XMLPreferencesSoftwareCounters
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "range", xmlSCRangeInstance );
        ar & boost::serialization::make_nvp( "algorithm", xmlSCAlgorithmInstance );
      }

      XMLPreferencesSoftwareCountersRange xmlSCRangeInstance;
      XMLPreferencesSoftwareCountersAlgorithm xmlSCAlgorithmInstance;
    };
/*
    struct XMLPreferencesCommunicationsFusion
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "sample_interval", sampleInterval );
        ar & boost::serialization::make_nvp( "inter_comm_interval", interCommInterval );
      }
    };
*/

    struct XMLPreferencesFilters
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "filter_trace_up_to_MB", filterTraceUpToMB );
        ar & boost::serialization::make_nvp( "xml_path", xmlPath );
        if ( version >= 1 )
        {
          ar & boost::serialization::make_nvp( "cutter", xmlCutterInstance );
          if ( version >= 2 )
          {
            ar & boost::serialization::make_nvp( "filter", xmlFilterInstance );
            if ( version >= 3 )
            {
              ar & boost::serialization::make_nvp( "software_counters", xmlSoftwareCountersInstance );
            }
          }
        }
      }

      float filterTraceUpToMB;
      std::string xmlPath;

      // Second level xml; needed a variable.
      // Next filters, same way.
      XMLPreferencesCutter xmlCutterInstance;
      XMLPreferencesFilter xmlFilterInstance;
      XMLPreferencesSoftwareCounters xmlSoftwareCountersInstance;
      // XMLPreferenecesCommunicationsFusion xmlCommunicationsFusionInstance;

    } xmlFilters;


    struct XMLPreferencesExternalApplications
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "text_editors", myTextEditors );
        ar & boost::serialization::make_nvp( "pdf_readers", myPDFReaders );
      }

      std::vector< std::string > myTextEditors;
      std::vector< std::string > myPDFReaders;

    } xmlExternalApplications;


    struct XMLPreferencesColor
    {
      template< class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & boost::serialization::make_nvp( "timeline_background", timelineBackground );
        ar & boost::serialization::make_nvp( "timeline_axis", timelineAxis );
        if( version >= 1 )
        {
          ar & boost::serialization::make_nvp( "timeline_use_color_zero", useColorZero );
          ar & boost::serialization::make_nvp( "timeline_semantic_zero", timelineColorZero );
          if( version >= 2 )
          {
            ar & boost::serialization::make_nvp( "timeline_color_punctual", timelineColorPunctual );
            if( version >= 4 )
            {
              ar & boost::serialization::make_nvp( "timeline_zero_dash_line", timelineZeroDashLine );
            }
          }
        }
        ar & boost::serialization::make_nvp( "timeline_logical_communications", timelineLogicalCommunications );
        ar & boost::serialization::make_nvp( "timeline_physical_communications", timelinePhysicalCommunications );
        ar & boost::serialization::make_nvp( "top_gradient", topGradient );
        ar & boost::serialization::make_nvp( "low_gradient", lowGradient );
        ar & boost::serialization::make_nvp( "begin_gradient", beginGradient );
        ar & boost::serialization::make_nvp( "end_gradient", endGradient );
        if( version >= 3 )
        {
          ar & boost::serialization::make_nvp( "begin_negative_gradient", beginNegativeGradient );
          ar & boost::serialization::make_nvp( "end_negative_gradient", endNegativeGradient );
        }
      }

      rgb timelineBackground;
      rgb timelineAxis;
      rgb timelineZeroDashLine;
      bool useColorZero;
      rgb timelineColorZero;
      rgb timelineColorPunctual;
      rgb timelineLogicalCommunications;
      rgb timelinePhysicalCommunications;
      rgb topGradient;
      rgb lowGradient;
      rgb beginGradient;
      rgb endGradient;
      rgb beginNegativeGradient;
      rgb endNegativeGradient;

    } xmlColor;


    template< class Archive >
    void serialize( Archive & ar, const unsigned int version )
    {
      if ( version == 0 )
      {
        PRV_UINT32 prec;
        TObjectOrder columns;
        bool units;
        bool thousSep;
        bool fillGaps;
        ar & boost::serialization::make_nvp( "precision", prec );
        ar & boost::serialization::make_nvp( "histoNumColumns", columns );
        ar & boost::serialization::make_nvp( "showUnits", units );
        ar & boost::serialization::make_nvp( "thousandSep", thousSep );
        ar & boost::serialization::make_nvp( "fillStateGaps", fillGaps );
        return;
      }

      ar & boost::serialization::make_nvp( "global", xmlGlobal );
      ar & boost::serialization::make_nvp( "timeline", xmlTimeline );
      ar & boost::serialization::make_nvp( "histogram", xmlHistogram );
      ar & boost::serialization::make_nvp( "filters", xmlFilters );
      ar & boost::serialization::make_nvp( "color", xmlColor );
      if (version >= 2)
      {
        ar & boost::serialization::make_nvp( "applications", xmlExternalApplications );
      }
    }
};

// First version: non structured, five xml tags
// BOOST_CLASS_VERSION( ParaverConfig, 0)

// Second version: introducing some structure
BOOST_CLASS_VERSION( ParaverConfig, 2 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesGlobal, 9 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesTimeline, 4 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesHistogram, 7 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesCutter, 1 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesFilter, 0 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesSoftwareCountersRange, 0 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesSoftwareCountersAlgorithm, 0 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesSoftwareCounters, 0 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesFilters, 3 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesExternalApplications, 0 )
BOOST_CLASS_VERSION( ParaverConfig::XMLPreferencesColor, 4 )

// WhatWhere.num_decimals
class WWNumDecimals: public PropertyFunction
{
  void parseLine( std::istringstream& line, ParaverConfig& config );
};

// Analyzer2D.num_columns
class HistoNumColumns: public PropertyFunction
{
  void parseLine( std::istringstream& line, ParaverConfig& config );
};

// Analyzer2D.units
class HistoUnits: public PropertyFunction
{
  void parseLine( std::istringstream& line, ParaverConfig& config );
};

// Analyzer2D.thousandsep
class HistoThousanSep: public PropertyFunction
{
  void parseLine( std::istringstream& line, ParaverConfig& config );
};

#endif // PARAVERCONFIG_H_INCLUDED
