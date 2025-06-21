// Google speech-to-text
#include "google/cloud/speech/v2/speech_client.h"
#include "google/cloud/speech/v2/speech_connection.h"
#include "google/cloud/project.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include "googlespeechtotext.h"

#define CAPTURE_LENGTH 3 // seconds

extern bool debug;
extern char *voiceString;

// Google speech interface

namespace speech = ::google::cloud::speech::v2;

void ConfigureRecognizer(speech::RecognizeRequest &request)
{
    *request.mutable_config()->add_language_codes() = "en-US";
    request.mutable_config()->set_model("long"); // or short
    *request.mutable_config()->mutable_auto_decoding_config() = {};
}

bool GoogleSpeechToText::VoiceParsing(const char *projectId, const char *fileName)
{
    bool ret = true;

    try
    {
        std::string const project_id = projectId;
        std::string const audio_file_path = fileName;

        std::ifstream audio_file(audio_file_path, std::ios::binary);
        if (!audio_file.is_open())
        {
            printf("ERROR: VoiceParsing(): Could not open audio file: %s\n", audio_file_path);
            return ret;
        }

        std::string audio_content((std::istreambuf_iterator<char>(audio_file)), std::istreambuf_iterator<char>());

        speech::RecognizeRequest request;
        ConfigureRecognizer(request);
        request.set_content(audio_content);
        request.set_recognizer("projects/" + project_id + "/locations/global/recognizers/_");

        auto client = ::google::cloud::speech_v2::SpeechClient(::google::cloud::speech_v2::MakeSpeechConnection());
        auto result = client.Recognize(request);

        if (!result)
        {
            printf("ERROR: VoiceParsing(): %s\n", result.status());
            return ret;
        }

        for (auto const &response : result->results())
        {
            if (response.alternatives().size() > 0 && !response.alternatives()[0].transcript().empty())
            {
                strcpy(::voiceString, response.alternatives()[0].transcript().c_str());
                if (::debug)
                    printf("Transcript: %s\n", ::voiceString);
                ret = false;
            }
            else
            {
                if (::debug)
                    printf("WARNING: VoiceParsing():response.alternatives() either has zero size, or its transcript is empty\n");
                return ret;
            }
        }
    }
    catch (...)
    {
        printf("ERROR: VoiceParsing(): Exception\n");
    }

    return ret;
}
