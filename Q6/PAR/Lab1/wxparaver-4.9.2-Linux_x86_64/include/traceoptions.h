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


#ifndef TRACEOPTIONS_H_INCLUDED
#define TRACEOPTIONS_H_INCLUDED

class KernelConnection;
#include "localkernel.h"

class TraceOptions
{
  public:
    struct allowed_types
    {
      TEventType type;
      TEventType max_type;  /* For range of types */
      unsigned long long min_call_time; /* For filtering calls by time */
      TEventValue value[20];
      int last_value;
    };

    typedef char TTasksList[256];
    typedef char *TStateNames[20];
    typedef struct allowed_types TFilterTypes[20];

    static TraceOptions *create( const KernelConnection *whichKernel );

    static bool isTraceToolsOptionsFile( const std::string& xmlFileName );
    static bool validTraceToolsOptionsFile( const std::string& xmlFileName );

    TraceOptions() {}
    TraceOptions( const KernelConnection *whichKernel ) {}
    virtual ~TraceOptions() {}

    /* Global Settings */
    virtual void set_max_trace_size( int traceSize )
    {}

    virtual int get_max_trace_size( ) const
    { return 0; }

    /* Sets for Cutter */
    virtual void set_by_time( bool whichByTime )
    {}
    virtual void set_min_cutting_time( unsigned long long minCutTime )
    {}
    virtual void set_max_cutting_time( unsigned long long maxCutTime )
    {}
    virtual void set_minimum_time_percentage( unsigned long long whichMinimumTimePercentage )
    {}
    virtual void set_maximum_time_percentage( unsigned long long whichMaximumTimePercentage )
    {}
    virtual void set_tasks_list( char *tasksList )
    {}
    virtual void set_original_time( bool originalTime )
    {}
    virtual void set_break_states( bool breakStates )
    {}
    virtual void set_remFirstStates( bool remStates )
    {}
    virtual void set_remLastStates( bool remStates )
    {}
    virtual void set_keep_events( bool keepEvents )
    {}

    virtual bool get_by_time() const
    { return false; }
    virtual unsigned long long get_min_cutting_time() const
    { return 0; }
    virtual unsigned long long get_max_cutting_time() const
    { return 0; }
    virtual unsigned long long get_minimum_time_percentage() const
    { return 0; }
    virtual unsigned long long get_maximum_time_percentage() const
    { return 0; }
    virtual void get_tasks_list( TTasksList &whichTasksList ) const
    { }
    virtual bool get_original_time() const
    { return 0; }
    virtual bool get_break_states() const
    { return 0; }
    virtual bool get_remFirstStates() const
    { return 0; }
    virtual bool get_remLastStates() const
    { return 0; }
    virtual bool get_keep_events() const
    { return 0; }


    /* Sets for filtering */
    virtual void set_filter_events( bool filterEvents )
    {}
    virtual void set_filter_states( bool filterStates )
    {}
    virtual void set_filter_comms( bool filterComms )
    {}
    virtual void set_discard_given_types( bool discardGivenTypes )
    {}
    virtual void set_filter_by_call_time( bool filterByCallTime )
    {}
    virtual void set_state_names( TStateNames stateNames )
    {}
    virtual void set_all_states( bool allStates )
    {}
    virtual void set_min_state_time( unsigned long long minStateTime )
    {}
    virtual void set_min_comm_size( int minCommSize )
    {}
    virtual void set_filter_types( TFilterTypes filterTypes )
    {}
    virtual void set_filter_last_type( int filterLastType )
    {}

    virtual bool get_filter_events() const
    { return 0; }
    virtual bool get_filter_states() const
    { return 0; }
    virtual bool get_filter_comms() const
    { return 0; }
    virtual bool get_discard_given_types() const
    { return 0; }
    virtual bool get_filter_by_call_time() const
    { return 0; }
    virtual void get_state_names( TStateNames &stateNames ) const
    {}
    virtual void get_state_names( std::string &stateList ) const
    {}
    virtual bool get_all_states() const
    { return 0; }
    virtual unsigned long long get_min_state_time() const
    { return 0; }
    virtual int get_min_comm_size() const
    { return 0; }
    virtual void get_filter_types( TFilterTypes &filterTypes ) const
    {}
    virtual int get_filter_last_type() const
    { return 0; }

    /* Sets for Software Counters */
    virtual void set_sc_onInterval( bool scOnInterval )
    {}
    virtual void set_sc_sampling_interval( unsigned long long scInterval )
    {}
    virtual void set_sc_minimum_burst_time( unsigned long long scInterval )
    {}
    virtual void set_sc_global_counters( bool scGlobalCounters )
    {}
    virtual void set_sc_acumm_counters( bool scAcummCounters )
    {}
    virtual void set_sc_summarize_states( bool scSummarizeStates )
    {}
    virtual void set_sc_only_in_bursts( bool scOnlyInBursts )
    {}
    virtual void set_sc_remove_states( bool scRemoveStates )
    {}
    virtual void set_sc_frequency( int scFrequency )
    {}
    virtual void set_sc_types( char *whichTypes )
    {}
    virtual void set_sc_types_kept( char *typesKept )
    {}

    virtual bool get_sc_onInterval() const
    { return 0; }
    virtual unsigned long long get_sc_sampling_interval() const
    { return 0; }
    virtual unsigned long long get_sc_minimum_burst_time() const
    { return 0; }
    virtual bool get_sc_global_counters() const
    { return 0; }
    virtual bool get_sc_acumm_counters() const
    { return 0; }
    virtual bool get_sc_summarize_states() const
    { return 0; }
    virtual bool get_sc_only_in_bursts() const
    { return 0; }
    virtual bool get_sc_remove_states() const
    { return 0; }
    //virtual unsigned long long get_sc_interval()
    //{ return 0; }
    virtual char *get_sc_types() const
    { return (char *)NULL; }
    virtual char *get_sc_types_kept() const
    { return (char *)NULL; }

    /* Sets for comm_fusion */
    virtual void set_reduce_comms( char reduceComms )
    {}
    virtual void set_comm_fusion_big_interval( unsigned long long bigInterval )
    {}
    virtual void set_comm_fusion_small_interval( unsigned long long smallInterval )
    {}

    /* Parameters for Stats */
    virtual void set_bursts_plot( int burstsPlot )
    {}
    virtual void set_comms_plot( int commsPlot )
    {}
    virtual void set_events_plot( int eventsPlot )
    {}

    virtual std::vector< std::string > parseDoc( char *docname )
    {
      std::vector< std::string > v;
      return v;
    }

    virtual bool saveXML( std::vector< std::string > &filterOrder, std::string fileName )
    {
      return true;
    }


    virtual TraceOptions *getConcrete()
    {
      return NULL;
    }

  protected:
  //  KernelConnection *myKernel;
};


class TraceOptionsProxy :public TraceOptions
{
  public:
    virtual ~TraceOptionsProxy();

    /* Global Settings */
    virtual void set_max_trace_size( int traceSize );
    virtual int get_max_trace_size() const;

    /* Sets for Cutter */
    virtual void set_by_time( bool whichByTime );
    virtual void set_min_cutting_time( unsigned long long minCutTime );
    virtual void set_max_cutting_time( unsigned long long maxCutTime );
    virtual void set_minimum_time_percentage( unsigned long long whichMinimumTimePercentage );
    virtual void set_maximum_time_percentage( unsigned long long whichMaximumTimePercentage );
    virtual void set_tasks_list( char *tasksList );
    virtual void set_original_time( bool originalTime );
    virtual void set_break_states( bool breakStates );
    virtual void set_remFirstStates( bool remStates );
    virtual void set_remLastStates( bool remStates );
    virtual void set_keep_events( bool keepEvents );

    virtual bool get_by_time() const;
    virtual unsigned long long get_min_cutting_time() const;
    virtual unsigned long long get_max_cutting_time() const;
    virtual unsigned long long get_minimum_time_percentage() const;
    virtual unsigned long long get_maximum_time_percentage() const;
    virtual void get_tasks_list( TTasksList &whichTasksList ) const;
    virtual bool get_original_time() const;
    virtual bool get_break_states() const;
    virtual bool get_remFirstStates() const;
    virtual bool get_remLastStates() const;
    virtual bool get_keep_events() const;

    /* Sets for filtering */
    virtual void set_filter_events( bool filterEvents );
    virtual void set_filter_states( bool filterStates );
    virtual void set_filter_comms( bool filterComms );
    virtual void set_discard_given_types( bool discardGivenTypes );
    virtual void set_filter_by_call_time( bool filterByCallTime );
    virtual void set_state_names( TStateNames stateNames );
    virtual void set_all_states( bool allStates );
    virtual void set_min_state_time( unsigned long long minStateTime );
    virtual void set_min_comm_size( int minCommSize );
    virtual void set_filter_types( TFilterTypes filterTypes );
    virtual void set_filter_last_type( int filterLastType );

    virtual bool get_filter_events() const;
    virtual bool get_filter_states() const;
    virtual bool get_filter_comms() const;
    virtual bool get_discard_given_types() const;
    virtual bool get_filter_by_call_time() const;
    virtual void get_state_names( TStateNames &stateNames ) const;
    virtual void get_state_names( std::string &stateList ) const;
    virtual bool get_all_states() const;
    virtual unsigned long long get_min_state_time() const;
    virtual int get_min_comm_size() const;
    virtual void get_filter_types( TFilterTypes &filterTypes ) const;
    virtual int get_filter_last_type() const;

    /* Sets for Software Counters */
    virtual void set_sc_onInterval( bool scOnInterval );
    virtual void set_sc_sampling_interval( unsigned long long scInterval );
    virtual void set_sc_minimum_burst_time( unsigned long long scInterval );
    virtual void set_sc_global_counters( bool scGlobalCounters );
    virtual void set_sc_acumm_counters( bool scAcummCounters );
    virtual void set_sc_summarize_states( bool scSummarizeStates );
    virtual void set_sc_only_in_bursts( bool scOnlyInBursts );
    virtual void set_sc_remove_states( bool scRemoveStates );
    virtual void set_sc_frequency( int scFrequency );
    virtual void set_sc_types( char *whichTypes );
    virtual void set_sc_types_kept( char *typesKept );

    virtual bool get_sc_onInterval() const;
    virtual unsigned long long get_sc_sampling_interval() const;
    virtual unsigned long long get_sc_minimum_burst_time() const;
    virtual bool get_sc_global_counters() const;
    virtual bool get_sc_acumm_counters() const;
    virtual bool get_sc_summarize_states() const;
    virtual bool get_sc_only_in_bursts() const;
    virtual bool get_sc_remove_states() const;
    virtual char *get_sc_types() const;
    virtual char *get_sc_types_kept() const;

    /* Sets for comm_fusion */
    virtual void set_reduce_comms( char reduceComms );
    virtual void set_comm_fusion_big_interval( unsigned long long bigInterval );
    virtual void set_comm_fusion_small_interval( unsigned long long smallInterval );

    /* Parameters for Stats */
    virtual void set_bursts_plot( int burstsPlot );
    virtual void set_comms_plot( int commsPlot );
    virtual void set_events_plot( int eventsPlot );

    virtual std::vector< std::string > parseDoc( char *docname );
    bool saveXML( std::vector< std::string > &filterOrder, std::string fileName );

    virtual TraceOptions *getConcrete();

    static std::vector< std::string > getIDsAvailableTraceTools();
    static std::string getTraceToolName( const std::string& toolID );
    static std::string getTraceToolExtension( const std::string& toolID );

  protected:

  private:
    TraceOptions *myTraceOptions;

    static std::vector< std::string > IDsAvailableTraceTools;

    // TraceOptionsProxy( const KernelConnection *whichKernel, char *xmldocname );
    TraceOptionsProxy( const KernelConnection *whichKernel );

    // friend TraceOptions *TraceOptions::create( KernelConnection *, char * );
    friend TraceOptions *TraceOptions::create( const KernelConnection * );
    friend TraceCutter *LocalKernel::newTraceCutter( TraceOptions *options,
                                         const std::vector< TEventType > &whichTypesWithValuesZero ) const;
    friend TraceFilter *LocalKernel::newTraceFilter( char *trace_in,
                                          char *trace_out,
                                          TraceOptions *options,
                                          const std::map< TTypeValuePair, TTypeValuePair >& whichTranslationTable,
                                          ProgressController *progress ) const;
};


#endif // TRACEOPTIONS_H_INCLUDED
