/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef _SOC_MIRACASTPLAYER_H_
#define _SOC_MIRACASTPLAYER_H_

#include <stdint.h>
#include <string>
#include <gst/gst.h>
#include <gst/audio/audio.h>
 
extern "C" {
    void SoC_ConfigureVideoDecodeErrorPolicy(void);
    GstElement* SoC_GetAudioSinkProperty(void);
    gboolean SoC_ReleaseAudioSinkProperty(GstElement* audioSink);
}

#endif  /* _SOC_MIRACASTPLAYER_H_ */

