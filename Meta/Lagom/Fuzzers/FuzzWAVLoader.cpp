/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibAudio/WavLoader.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(uint8_t const* data, size_t size)
{
    if (!data)
        return 0;
    auto wav_data = ReadonlyBytes { data, size };
    auto wav_or_error = Audio::WavLoaderPlugin::try_create(wav_data);

    if (wav_or_error.is_error())
        return 0;

    auto wav = wav_or_error.release_value();

    for (;;) {
        auto samples = wav->get_more_samples();
        if (samples.is_error())
            return 2;
        if (samples.value().size() > 0)
            break;
    }

    return 0;
}
