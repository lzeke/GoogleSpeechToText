This is a very simple library used by the RobotCar project to speed up compilation and linking. This doesn't do anything else except wraps Google's speech-to-text APIs into a library.

The CMakeLists.txt file assumes that Google's speech-to-text APIs and their (huge) supporting infrastructure was installed by vcpkg, Microsoft's package manager, into the ~/vcpkg directory.
