from conans import ConanFile

class Ctti(ConanFile):
    name = "ctti"
    url = "https::/github.com/Manu343726/ctti"
    license = "MIT"
    version = "0.0.2"
    exports = "*.hpp"
    build_policy = "missing"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
