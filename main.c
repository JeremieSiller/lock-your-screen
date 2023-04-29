#include <CoreAudio/CoreAudio.h>
#include <string.h>

void getDeviceName(AudioDeviceID deviceID, char* deviceName) {
    AudioObjectPropertyAddress address = {
        kAudioDevicePropertyDeviceNameCFString,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMaster
    };
    CFStringRef cfDeviceName = NULL;
    UInt32 dataSize = sizeof(CFStringRef);
    OSStatus result = AudioObjectGetPropertyData(deviceID, &address, 0, NULL, &dataSize, &cfDeviceName);
    if (result == noErr && cfDeviceName != NULL) {
        CFStringGetCString(cfDeviceName, deviceName, 256, kCFStringEncodingUTF8);
        CFRelease(cfDeviceName);
    }
}

int main() {
    UInt32 propertySize;
    AudioObjectPropertyAddress propertyAddress;
    AudioDeviceID dev_array[64];
    int numberOfDevices = 0;
    char deviceName[256];

    propertyAddress.mSelector = kAudioHardwarePropertyDevices;
    propertyAddress.mScope = kAudioObjectPropertyScopeGlobal;
    propertyAddress.mElement = kAudioObjectPropertyElementMaster;

    propertySize = 0;
    AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize);
    numberOfDevices = propertySize / sizeof(AudioDeviceID);

    AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &propertySize, dev_array);

    AudioDeviceID speaker_id;
    for (int i = 0; i < numberOfDevices; ++i) {
        getDeviceName(dev_array[i], deviceName);
        if (strcmp(deviceName, "iMac Speakers") == 0) {
            speaker_id = dev_array[i];
            break;
        }
    }

    propertyAddress.mSelector = kAudioHardwarePropertyDefaultOutputDevice;
    propertyAddress.mScope = kAudioObjectPropertyScopeGlobal;
    propertyAddress.mElement = kAudioObjectPropertyElementMaster;
    propertySize = sizeof(AudioDeviceID);
    AudioObjectSetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, propertySize, &speaker_id);
}