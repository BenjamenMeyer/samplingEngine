+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Tested        | Function/Pragma/Structure                                                             | File                                                   |
+===============+=======================================================================================+========================================================+
| Yes           | SAMPLING_ENGINE_MASK_ERROR_VALUE                                                      | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | SAMPLING_ENGINE_IS_ERROR_CODE                                                         | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | SAMPLING_ENGINE_GET_ERROR_CODE                                                        | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | SAMPLING_ENGINE_MAKE_ERROR_CODE                                                       | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | SAMPLING_ENGINE_MATCHES_ERROR_CODE                                                    | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | SAMPLING_ENGINE_CHECK_SUCCESS                                                         | samplingEngine/error_codes.h                           |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::samplingEngineLogger()                 | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::logging::samplingEngineLogger::~samplingEngineLogger()                | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::emergency()                            | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::alert()                                | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::critical()                             | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::error()                                | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::warn()                                 | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::notice()                               | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::info()                                 | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::logging::samplingEngineLogger::debug()                                | samplingEngine/log.h                                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::queues::record_container                                              | samplingEngine/record_queues.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a (STL)     | samplingEngine::queues::record_queue                                                  | samplingEngine/record_queues.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::config::tachometerConfiguration                                       | samplingEngine/configuration.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::config::sampleConfiguration                                           | samplingEngine/configuration.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::config::sensorConfiguration                                           | samplingEngine/configuration.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::config::engineConfiguration                                           | samplingEngine/configuration.h                         |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::channels::channel_config                                              | samplingEngine/channels/channel.h                      |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a (STL)     | samplingEngine::channels::channelList                                                 | samplingEngine/channels/channel.h                      |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::channels::NORMALIZED_TO_SCALAR (int, float, etc)                      | samplingEngine/channels/channel.h                      |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::channels::SCALAR_TO_NORMALIZED (int, float, etc)                      | samplingEngine/channels/channel.h                      |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::records::status_record_entry                                          | samplingEngine/records/status_record.h                 |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::records::status_record                                                | samplingEngine/records/status_record.h                 |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::records::time_record                                                  | samplingEngine/records/time_record.h                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::records::time_indexes                                                 | samplingEngine/records/distance_record.h               |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| n/a           | samplingEngine::records::distance_record                                              | samplingEngine/records/distance_record.h               |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::coreSamplingEngine                          | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::~coreSamplingEngine                         | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::open()                                      | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::isOpen()                                    | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::core::coreSamplingEngine::initialize()                                | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::close()                                     | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::processRecord()                             | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::getTimeRecordType()                         | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::getDistanceRecordType()                     | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::getDataRecord()                             | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::getStatusRecord()                           | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::core::coreSamplingEngine::getTimeRecord()                             | samplingEngine/core.h                                  |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::samplingEngine()                                      | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::~samplingEngine()                                     | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::samplingEngine::setLogger()                                           | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| Yes           | samplingEngine::samplingEngine::getErrorMessage                                       | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getState()                                            | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::initialize()                                          | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::shutdown()                                            | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::close()                                               | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::processRecord()                                       | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getTimeRecordType()                                   | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getDistanceRecordType()                               | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getDataRecord()                                       | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getStatusRecord()                                     | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::getTimeRecord()                                       | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::setState()                                            | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::enableState()                                         | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::disableState()                                        | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::samplingEngine::isStateSet()                                          | samplingEngine/engine.h                                |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::geometricEngine()                                   | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::~geometricEngine()                                  | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::open()                                              | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::isOpen()                                            | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::initialize()                                        | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::close()                                             | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::addFilter()                                         | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::addInterdependentFilters()                          | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::processRecord()                                     | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::getTimeRecordType()                                 | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::getDistanceRecordType()                             | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::getDataRecord()                                     | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::getStatusRecord()                                   | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::getTimeRecord()                                     | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::cleanup_record()                                    | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | geometricEngine::geometricEngine::process_records()                                   | samplingEngineInternal/geometricEngine/engine.h        |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::AveragingFilter()                                           | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::~AveragingFilter()                                          | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::initialize()                                                | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::destroy()                                                   | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::apply()                                                     | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::get()                                                       | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilter::getLength()                                                 | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterInt8                                                          | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterUInt8                                                         | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterInt16                                                         | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterUInt16                                                        | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterInt32                                                         | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterUInt32                                                        | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterInt64                                                         | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterUInt64                                                        | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterFloat                                                         | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | filters::AveragingFilterDouble                                                        | samplingEngineInternal/filters/averaging.h             |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::filterNameList                                            | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilterList                                        | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::abstractFilter()                          | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::~abstractFilter()                         | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::filterName()                              | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::filterDependencies()                      | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::isTimeBasedFilter()                       | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::isDistanceBasedFilter()                   | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::open()                                    | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::isOpen()                                  | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::reset()                                   | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::close()                                   | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::required_samples()                        | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::processRecord(records::time_record)       | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::processRecord(records::distance_record)   | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::updateRecord(records::time_record)        | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::updateRecord(records::distance_record)    | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::updateRecord(records::status_record)      | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::setTimeRecordInputIndex()                 | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::setTimeRecordOutputIndex()                | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::setDistanceRecordOutputIndex()            | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::add_dependencies()                        | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::interfaces::abstractFilter::reset_dependencies()                      | samplingEngineInternal/interfaces/abstractFilter.h     |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
| No            | samplingEngine::send_to_log()                                                         | samplingEngineInternal/logging/log.h                   |
+---------------+---------------------------------------------------------------------------------------+--------------------------------------------------------+
