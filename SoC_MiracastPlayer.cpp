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

#include <cmath>

#include "SoC_MiracastPlayer.h"
#include "halLogger.h"

static GstElement* m_audio_sink = nullptr;

void SoC_ConfigureVideoDecodeErrorPolicy(void)
{
    LOG_INFO("Error, policy not defined.");
}

GstElement* SoC_GetAudioSinkProperty(void)
{
    LOG_INFO("Not yet implemented.");
    return m_audio_sink;
}

gboolean SoC_ReleaseAudioSinkProperty(GstElement* audioSink)
{
	if (audioSink == nullptr) {
		LOG_ERR("Audio sink is null, cannot release.");
		return false;
	}
    LOG_INFO("Not yet implemented.");
    return false;
}
