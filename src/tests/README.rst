Sampling Engine Unit Testing
============================

This directory contains a series of unit tests for the Sampling Engine.
The unit tests are based on the Boost Unit Test Framework and built
as a normal part of the library build process. To run the tests do:

.. codeblock:: shell

	$ make test

The tests are structured along the same lines as the main modules:

	- engines
	- measurements
	- filters

There should be at least 1 test implementation file per normal
implementation file. Test files may exceed in order to produce
full unit test coverage of the functionality.
