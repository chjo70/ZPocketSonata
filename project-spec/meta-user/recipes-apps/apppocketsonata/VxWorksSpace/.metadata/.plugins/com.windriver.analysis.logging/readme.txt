How to change the logging detail level in the logging.properties file

Each of the *.Level values in logging.properties may be set to any of the following to
control the granularity of messages which will be emitted from the corresponding logger:

    OFF
    SEVERE
    WARNING
    INFO
    CONFIG
    FINE
    FINER
    FINEST
    ALL

DEBUGGING
=========
Debugging output is limited globally by setting the level of
    com.windriver.analysis.instruments.file.console.debug.Level
to any of the above values.

For each detail debug logger, i.e. its name starts with 
    com.windriver.analysis.instruments.file.console.debug
the level of detail output from it may be controlled by setting
its .Level to any one of the above values.
The level of detail output will be limited by the value set for
    com.windriver.analysis.instruments.file.console.debug.Level

To have the level of a detail debug logger follow the value set for
com.windriver.analysis.instruments.file.console.debug,
just set the .Level for the detail logger to null
