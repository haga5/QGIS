/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/server/qgsserversettings.h                                       *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/







class QgsServerSettings
{
%Docstring
 QgsServerSettings provides a way to retrieve settings by prioritizing
 according to environment variables, ini file and default values.
.. versionadded:: 3.0
%End

%TypeHeaderCode
#include "qgsserversettings.h"
%End
  public:

    QgsServerSettings();
%Docstring
 Constructor.
%End

    void load();
%Docstring
 Load settings according to current environment variables.
%End

    bool load( const QString &envVarName );
%Docstring
 Load setting for a specific environment variable name.
 :return: true if loading is successful, false in case of an invalid name.
 :rtype: bool
%End

    void logSummary() const;
%Docstring
 Log a summary of settings currently loaded.
%End

    QString iniFile() const;
%Docstring
 Returns the ini file loaded by QSetting.
 :return: the path of the ini file or an empty string if none is loaded.
 :rtype: str
%End

    bool parallelRendering() const;
%Docstring
 Returns parallel rendering setting.
 :return: true if parallel rendering is activated, false otherwise.
 :rtype: bool
%End

    int maxThreads() const;
%Docstring
 Returns the maximum number of threads to use.
 :return: the number of threads.
 :rtype: int
%End

    int maxCacheLayers() const;
%Docstring
 Returns the maximum number of cached layers.
 :return: the number of cached layers.
 :rtype: int
%End

    QgsMessageLog::MessageLevel logLevel() const;
%Docstring
 Returns the log level.
 :return: the log level.
 :rtype: QgsMessageLog.MessageLevel
%End

    QString projectFile() const;
%Docstring
 Returns the QGS project file to use.
 :return: the path of the QGS project or an empty string if none is defined.
 :rtype: str
%End

    QString logFile() const;
%Docstring
 Returns the log file.
 :return: the path of the log file or an empty string if none is defined.
 :rtype: str
%End

    qint64 cacheSize() const;
%Docstring
 Returns the cache size.
 :return: the cache size.
 :rtype: qint64
%End

    QString cacheDirectory() const;
%Docstring
 Returns the cache directory.
 :return: the directory.
 :rtype: str
%End

};

/************************************************************************
 * This file has been generated automatically from                      *
 *                                                                      *
 * src/server/qgsserversettings.h                                       *
 *                                                                      *
 * Do not edit manually ! Edit header and run scripts/sipify.pl again   *
 ************************************************************************/
