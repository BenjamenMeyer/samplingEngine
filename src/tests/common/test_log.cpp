#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN

#include <functional>
#include <string>

#include <boost/test/unit_test.hpp>

#include <samplingEngine/log.h>
#include <samplingEngineTesting/testing/log/testLogger.h>


class callbackKeeper: public testLoggerCallback
	{
	public:
		callbackKeeper()
			{
			}

		void callback(samplingEngine::LOG_LEVELS _level, const char* _message)
			{
			theLevel = _level;
			theMessage = std::string(_message);
			}

		samplingEngine::LOG_LEVELS level() const
			{
			return theLevel;
			}

		std::string message() const
			{
			return theMessage;
			}

	protected:
		std::string theMessage;
		samplingEngine::LOG_LEVELS theLevel;
	};


BOOST_AUTO_TEST_SUITE( Common );

BOOST_AUTO_TEST_CASE( CommonLogger_Instantiation )
{
    testLogger logger;
	samplingEngine::logging::samplingEngineLogger* nullLogger = NULL;
	samplingEngine::logging::samplingEngineLogger* ptrLogger = dynamic_cast<samplingEngine::logging::samplingEngineLogger*>(&logger);

	BOOST_CHECK_PREDICATE(std::not_equal_to<samplingEngine::logging::samplingEngineLogger*>(), (nullLogger)(ptrLogger) );
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogEmergency )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Emergency";
	logger.emergency(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_EMERGENCY, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogAlert )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Alert";
	logger.alert(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_ALERT, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogCritical )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Critical";
	logger.critical(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_CRITICAL, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogError )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Error";
	logger.error(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_ERROR, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogWarning )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Warning";
	logger.warn(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_WARN, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogNotice )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Notice";
	logger.notice(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_NOTICE, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogInfo )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Info";
	logger.info(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_INFO, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}

BOOST_AUTO_TEST_CASE( CommonLogger_LogDebug )
{
	callbackKeeper keeper;
	testLogger logger(&keeper);

	std::string message = "Testing Debug";
	logger.debug(message.c_str());
	
	BOOST_CHECK_EQUAL(samplingEngine::LOG_LEVEL_DEBUG, keeper.level());
	BOOST_CHECK_EQUAL(message, keeper.message());
}


BOOST_AUTO_TEST_SUITE_END();
