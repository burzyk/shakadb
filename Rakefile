require 'rake'
require 'fileutils'

BUILD_DIR='./build'
BINARIES_DIR=BUILD_DIR + '/bin'
TESTS_DIR=BUILD_DIR + '/tests'
INTEGRATION_TESTS_DATA_DIR=BUILD_DIR + '/integration-tests'
PYTHON_WRAPPER_DIR='./wrappers/python'

def start_test_instance()
    puts "Starting test instance ..."

    FileUtils.rm_rf(INTEGRATION_TESTS_DATA_DIR) if Dir.exists?(INTEGRATION_TESTS_DATA_DIR)
    Dir.mkdir(INTEGRATION_TESTS_DATA_DIR)

    sh('shakadb -d $PWD/' + INTEGRATION_TESTS_DATA_DIR + ' &> /dev/null &')
end

def stop_test_instance()
    puts "Stopping test instance ..."
    sh('killall shakadb -s USR1')
end

def run_python_tests()
    sh('python3 -m pip install pytest')
    sh('PYTHONPATH=$PWD/' + PYTHON_WRAPPER_DIR + ' pytest ' + PYTHON_WRAPPER_DIR + '/tests/*.py')
end

task :default => [:build_binaries, :run_tests]

task :build_debug => [:default]
task :build_release => [:default, :run_integration_tests]

task :init do
    puts "Initializing build ..."

    FileUtils.rm_rf(BUILD_DIR) if Dir.exists?(BUILD_DIR)
    Dir.mkdir(BUILD_DIR)
    Dir.mkdir(BINARIES_DIR)
    Dir.mkdir(TESTS_DIR)
end

task :build_binaries => [:init] do
    sh('cmake -H. -B' + BINARIES_DIR)
    sh('cmake  --build ' + BINARIES_DIR + ' --target all -- -j 8')
end

task :run_tests => [:build_binaries] do
    puts "running tests ..."
    sh(BINARIES_DIR + '/shakadb.test ' + TESTS_DIR)
end

task :build_packages => [:run_tests] do
    sh('cd ' + BINARIES_DIR + ' && cpack && cd ../..')
end

task :start_test_instance do
    start_test_instance()
end

task :stop_test_instance do
    stop_test_instance()
end

task :run_integration_tests do
    sh('sudo cmake  --build ' + BINARIES_DIR + ' --target install')

    start_test_instance()
    sleep 1

    run_python_tests()

    sleep 1
    stop_test_instance()
end

