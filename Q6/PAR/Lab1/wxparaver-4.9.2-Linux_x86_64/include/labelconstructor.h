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


#ifndef LABELCONSTRUCTOR_H_INCLUDED
#define LABELCONSTRUCTOR_H_INCLUDED

#include <locale>
#include <sstream>
#include "paraverkerneltypes.h"
#include "paraverconfig.h"
#include "trace.h"

using boost::posix_time::ptime;

class Histogram;

class LabelConstructor
{
  public:
    static void init();

    static std::string objectLabel( TObjectOrder globalOrder,
                               TWindowLevel level,
                               Trace *whichTrace,
                               bool showLevelTag = true,
                               bool showRowText = true );

    static std::string histoColumnLabel( THistogramColumn whichColumn,
                                    const Window *whichWindow,
                                    THistogramLimit min,
                                    THistogramLimit max,
                                    THistogramLimit delta,
                                    bool shortLabels );

    static std::string histoCellLabel( const Histogram *whichHisto,
                                  TSemanticValue value,
                                  bool showUnits );

    static std::string histoTotalLabel( THistoTotals whichTotal );

    static std::string timeLabel( TTime value, TTimeUnit unit, PRV_UINT32 precision );

    static std::string timeLabel( ptime value, PRV_UINT32 precision );

    static std::string semanticLabel( const Window * whichWindow, TSemanticValue value,
                                 bool text, PRV_UINT32 precision, bool hexMode );

    static std::string eventLabel( Window *whichWindow,
                              TEventType whichType,
                              TSemanticValue whichValue,
                              bool text );

    static std::string eventTypeLabel( Window *whichWindow,
                                  TEventType whichType,
                                  bool text );

    static std::string eventValueLabel( Window *whichWindow,
                                   TEventType whichType,
                                   TSemanticValue whichValue,
                                   bool writeValueAsPrefix = false );

    static bool getTimeValue( const std::string& timeLabel,
                              TTimeUnit unit,
                              PRV_UINT32 precision,
                              TTime& value );

    static void transformToShort( std::string& onLabel, char beginDelimiter = '[', char endDelimiter = ']' );

    enum TGroupID
    {
      COLOR = 0,
      GRADIENT_FUNCTION,
      DRAWMODE,
      PIXEL_SIZE,
      IMAGE_FORMAT,
      TEXT_FORMAT,
      OBJECT_LABELS,
      OBJECT_AXIS
    };

    static void getGUIGroupLabels( const TGroupID group, std::vector< std::string > &labels );

    static std::string getDate( bool reverseOrder = false );

    static std::string getImageFileSuffix( const ParaverConfig::TImageFormat& format = ParaverConfig::PNG );
    static std::string getDataFileSuffix( const ParaverConfig::TTextFormat& format = ParaverConfig::PLAIN );

  private:
    static std::stringstream sstrObjectLabel;
    static std::stringstream label;
    static std::stringstream columnLabel;
    static std::stringstream tmp;
    static std::stringstream sstrTimeLabel;
    static std::stringstream sstrSemanticLabel;

    static std::string rowStr;
    static std::string tmpStr;
    static char separator;
    static char point;

    static std::locale myLocaleWithoutThousands;
    static std::locale myLocaleWithThousands;
};

#endif // LABELCONSTRUCTOR_H_INCLUDED
