#ifndef _EULER_H
#define _EULER_H

#include "plugin.h" 

class Euler: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
  private:
	  void calculateEuler();
	  int F, V, E, X;
	// add private methods and attributes here
};

#endif
