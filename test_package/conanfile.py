from conans import ConanFile, CMake
import os

version = os.getenv('CONAN_CTTI_VERSION', '0.0.1')
user    = os.getenv('CONAN_CTTI_USER', 'Manu343726')
channel = os.getenv('CONAN_CTTI_CHANNEL', 'testing')

class TestCtti(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    requires = (
        'ctti/{}@{}/{}'.format(version, user, channel)
    )
    generators = 'cmake'

    def build(self):
        cmake = CMake(self)
        self.run('cmake {} {}'.format(self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . {}'.format(cmake.build_config))

    def test(self):
        self.run(os.path.join('.', 'bin', 'example'))
