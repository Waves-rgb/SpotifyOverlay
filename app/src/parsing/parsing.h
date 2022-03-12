#pragma once

#include <string>

using namespace std;

struct SpotifyData {
    string title;
    string artist;
    string album;
    string albumArt;
    string duration;
    string progress;
};

namespace Parsing {
    SpotifyData parseSpotifyData(string data);
}