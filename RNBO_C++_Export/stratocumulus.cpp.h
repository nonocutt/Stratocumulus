/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 1;
}

void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->midiin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_02_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_03_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_04_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_05_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_06_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_07_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_08_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    this->ctlin_09_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    this->p_01_perform(this->signals[0], this->signals[1], this->signals[2], n);
    this->signalsend_01_perform(this->signals[0], this->signals[3], n);
    this->signalreceive_03_perform(this->signals[3], this->signals[0], n);
    this->signalsend_02_perform(this->signals[1], this->signals[3], n);
    this->signalreceive_04_perform(this->signals[3], this->signals[1], n);
    this->gen_02_perform(this->signals[2], this->signals[3], n);
    this->numbertilde_01_perform(this->signals[3], this->dummyBuffer, n);
    this->signalsend_03_perform(in1, this->signals[2], n);
    this->signalreceive_05_perform(this->signals[2], this->signals[4], n);

    this->gen_06_perform(
        this->signals[4],
        this->gen_06_minfreq,
        this->gen_06_maxfreq,
        this->gen_06_window_size,
        this->gen_06_threshold,
        this->gen_06_smooth_factor,
        this->gen_06_confidence_threshold,
        this->gen_06_hold_time,
        this->gen_06_hysteresis,
        this->gen_06_octave_correct,
        this->gen_06_process_rate,
        this->signals[2],
        n
    );

    this->gen_05_perform(this->signals[2], this->signals[4], n);
    this->ftom_tilde_01_perform(this->signals[4], this->signals[2], n);
    this->dspexpr_04_perform(this->signals[2], this->dspexpr_04_in2, this->signals[4], n);
    this->gen_04_perform(this->signals[4], this->signals[3], this->signals[2], n);
    this->numbertilde_02_perform(this->signals[2], this->dummyBuffer, n);
    this->dspexpr_03_perform(in1, this->dspexpr_03_in2, this->signals[2], n);
    this->signalsend_04_perform(this->signals[2], this->signals[3], n);
    this->signalreceive_01_perform(this->signals[3], this->signals[2], n);
    this->dspexpr_05_perform(in1, this->dspexpr_05_in2, this->signals[3], n);
    this->signalsend_05_perform(this->signals[3], this->signals[4], n);
    this->signalreceive_02_perform(this->signals[4], this->signals[3], n);

    this->gen_03_perform(
        this->signals[2],
        this->signals[3],
        this->signals[0],
        this->signals[1],
        this->gen_03_in5,
        out1,
        out2,
        n
    );

    this->recordtilde_01_perform(
        this->recordtilde_01_record,
        this->recordtilde_01_begin,
        this->recordtilde_01_end,
        in1,
        this->dummyBuffer,
        n
    );

    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 5; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->numbertilde_01_dspsetup(forceDSPSetup);
    this->gen_04_dspsetup(forceDSPSetup);
    this->numbertilde_02_dspsetup(forceDSPSetup);
    this->gen_03_dspsetup(forceDSPSetup);
    this->data_02_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->prepareToProcess(sampleRate, maxBlockSize, force);
    }

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 1;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    case 0:
        {
        return addressOf(this->sample);
        break;
        }
    case 1:
        {
        return addressOf(this->RNBODefaultSinus);
        break;
        }
    case 2:
        {
        return addressOf(this->norm_buffer);
        break;
        }
    case 3:
        {
        return addressOf(this->diff_buffer);
        break;
        }
    case 4:
        {
        return addressOf(this->yin_buffer);
        break;
        }
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 5;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (index == 0) {
        this->recordtilde_01_buffer = reInitDataView(this->recordtilde_01_buffer, this->sample);
        this->data_02_buffer = reInitDataView(this->data_02_buffer, this->sample);
        this->data_02_bufferUpdated();
    }

    if (index == 1) {
        this->gen_03_cycle_4_buffer = reInitDataView(this->gen_03_cycle_4_buffer, this->RNBODefaultSinus);
        this->gen_03_cycle_10_buffer = reInitDataView(this->gen_03_cycle_10_buffer, this->RNBODefaultSinus);
    }

    if (index == 2) {
        this->gen_06_norm_buffer = reInitDataView(this->gen_06_norm_buffer, this->norm_buffer);
    }

    if (index == 3) {
        this->gen_06_diff_buffer = reInitDataView(this->gen_06_diff_buffer, this->diff_buffer);
    }

    if (index == 4) {
        this->gen_06_yin_buffer = reInitDataView(this->gen_06_yin_buffer, this->yin_buffer);
    }

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->processDataViewUpdate(index, time);
    }
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);

    this->sample = initDataRef(
        this->sample,
        this->dataRefStrings->name0,
        false,
        this->dataRefStrings->file0,
        this->dataRefStrings->tag0
    );

    this->RNBODefaultSinus = initDataRef(
        this->RNBODefaultSinus,
        this->dataRefStrings->name1,
        true,
        this->dataRefStrings->file1,
        this->dataRefStrings->tag1
    );

    this->norm_buffer = initDataRef(
        this->norm_buffer,
        this->dataRefStrings->name2,
        true,
        this->dataRefStrings->file2,
        this->dataRefStrings->tag2
    );

    this->diff_buffer = initDataRef(
        this->diff_buffer,
        this->dataRefStrings->name3,
        true,
        this->dataRefStrings->file3,
        this->dataRefStrings->tag3
    );

    this->yin_buffer = initDataRef(
        this->yin_buffer,
        this->dataRefStrings->name4,
        true,
        this->dataRefStrings->file4,
        this->dataRefStrings->tag4
    );

    this->assign_defaults();
    this->applyState();
    this->sample->setIndex(0);
    this->recordtilde_01_buffer = new Float32Buffer(this->sample);
    this->data_02_buffer = new Float32Buffer(this->sample);
    this->RNBODefaultSinus->setIndex(1);
    this->gen_03_cycle_4_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->gen_03_cycle_10_buffer = new SampleBuffer(this->RNBODefaultSinus);
    this->norm_buffer->setIndex(2);
    this->gen_06_norm_buffer = new SampleBuffer(this->norm_buffer);
    this->diff_buffer->setIndex(3);
    this->gen_06_diff_buffer = new SampleBuffer(this->diff_buffer);
    this->yin_buffer->setIndex(4);
    this->gen_06_yin_buffer = new SampleBuffer(this->yin_buffer);
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters())
            this->p_01[0]->setPolyParameterValue(this->p_01, index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters())
            return this->p_01[0]->getPolyParameterValue(this->p_01, index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 9 + this->p_01[0]->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "Spread";
        }
    case 1:
        {
        return "Grain_Size";
        }
    case 2:
        {
        return "Density";
        }
    case 3:
        {
        return "Dry/Wet";
        }
    case 4:
        {
        return "Stereo";
        }
    case 5:
        {
        return "Release";
        }
    case 6:
        {
        return "Sustain";
        }
    case 7:
        {
        return "Decay";
        }
    case 8:
        {
        return "Attack";
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters()) {
            {
                return this->p_01[0]->getParameterName(index);
            }
        }

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "Spread";
        }
    case 1:
        {
        return "Grain_Size";
        }
    case 2:
        {
        return "Density";
        }
    case 3:
        {
        return "Dry/Wet";
        }
    case 4:
        {
        return "Stereo";
        }
    case 5:
        {
        return "Release";
        }
    case 6:
        {
        return "Sustain";
        }
    case 7:
        {
        return "Decay";
        }
    case 8:
        {
        return "Attack";
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters()) {
            {
                return this->p_01[0]->getParameterId(index);
            }
        }

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 160;
            info->min = 10;
            info->max = 500;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "ms";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 15;
            info->min = 0;
            info->max = 60;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 50;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 260;
            info->min = 10;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "ms";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 100;
            info->min = 0;
            info->max = 100;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "%";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 200;
            info->min = 10;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "ms";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 200;
            info->min = 0;
            info->max = 2000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "";
            info->unit = "ms";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 9;

            if (index < this->p_01[0]->getNumParameters()) {
                for (Index i = 0; i < 8; i++) {
                    this->p_01[i]->getParameterInfo(index, info);
                }
            }

            break;
            }
        }
    }
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 2:
        {
        {
            value = (value < 0 ? 0 : (value > 60 ? 60 : value));
            ParameterValue normalizedValue = (value - 0) / (60 - 0);
            return normalizedValue;
        }
        }
    case 0:
    case 3:
    case 4:
    case 6:
        {
        {
            value = (value < 0 ? 0 : (value > 100 ? 100 : value));
            ParameterValue normalizedValue = (value - 0) / (100 - 0);
            return normalizedValue;
        }
        }
    case 8:
        {
        {
            value = (value < 0 ? 0 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 0) / (2000 - 0);
            return normalizedValue;
        }
        }
    case 1:
        {
        {
            value = (value < 10 ? 10 : (value > 500 ? 500 : value));
            ParameterValue normalizedValue = (value - 10) / (500 - 10);
            return normalizedValue;
        }
        }
    case 5:
    case 7:
        {
        {
            value = (value < 10 ? 10 : (value > 2000 ? 2000 : value));
            ParameterValue normalizedValue = (value - 10) / (2000 - 10);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters()) {
            {
                return this->p_01[0]->convertToNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 2:
        {
        {
            {
                return 0 + value * (60 - 0);
            }
        }
        }
    case 0:
    case 3:
    case 4:
    case 6:
        {
        {
            {
                return 0 + value * (100 - 0);
            }
        }
        }
    case 8:
        {
        {
            {
                return 0 + value * (2000 - 0);
            }
        }
        }
    case 1:
        {
        {
            {
                return 10 + value * (500 - 10);
            }
        }
        }
    case 5:
    case 7:
        {
        {
            {
                return 10 + value * (2000 - 10);
            }
        }
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters()) {
            {
                return this->p_01[0]->convertFromNormalizedParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    default:
        {
        index -= 9;

        if (index < this->p_01[0]->getNumParameters()) {
            {
                return this->p_01[0]->constrainParameterValue(index, value);
            }
        }

        return value;
        }
    }
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-28") == objectId)
            this->message_03_listin_number_set(payload);

        break;
        }
    case TAG("sig"):
        {
        if (TAG("number~_obj-71") == objectId)
            this->numbertilde_01_sig_number_set(payload);

        if (TAG("number~_obj-21") == objectId)
            this->numbertilde_02_sig_number_set(payload);

        break;
        }
    case TAG("mode"):
        {
        if (TAG("number~_obj-71") == objectId)
            this->numbertilde_01_mode_set(payload);

        if (TAG("number~_obj-21") == objectId)
            this->numbertilde_02_mode_set(payload);

        break;
        }
    }

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->processNumMessage(tag, objectId, time, payload);
    }
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-28") == objectId)
            this->message_03_listin_list_set(payload);

        break;
        }
    case TAG("sig"):
        {
        if (TAG("number~_obj-71") == objectId)
            this->numbertilde_01_sig_list_set(payload);

        if (TAG("number~_obj-21") == objectId)
            this->numbertilde_02_sig_list_set(payload);

        break;
        }
    }

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->processListMessage(tag, objectId, time, payload);
    }
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("listin"):
        {
        if (TAG("message_obj-28") == objectId)
            this->message_03_listin_bang_bang();

        break;
        }
    case TAG("startupbang"):
        {
        if (TAG("loadbang_obj-24") == objectId)
            this->loadbang_01_startupbang_bang();

        break;
        }
    }

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->processBangMessage(tag, objectId, time);
    }
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("listout"):
        {
        return "listout";
        }
    case TAG("message_obj-28"):
        {
        return "message_obj-28";
        }
    case TAG("monitor"):
        {
        return "monitor";
        }
    case TAG("number~_obj-71"):
        {
        return "number~_obj-71";
        }
    case TAG("assign"):
        {
        return "assign";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("out3"):
        {
        return "out3";
        }
    case TAG(""):
        {
        return "";
        }
    case TAG("number~_obj-21"):
        {
        return "number~_obj-21";
        }
    case TAG("listin"):
        {
        return "listin";
        }
    case TAG("startupbang"):
        {
        return "startupbang";
        }
    case TAG("loadbang_obj-24"):
        {
        return "loadbang_obj-24";
        }
    case TAG("sig"):
        {
        return "sig";
        }
    case TAG("mode"):
        {
        return "mode";
        }
    }

    auto subpatchResult_0 = this->p_01[0]->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 1;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {
    case 0:
        {
        static const MessageInfo r0 = {
            "out3",
            Outport
        };

        return r0;
        }
    }

    return NullMessageInfo;
}

protected:

class RNBOSubpatcher_05 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_05()
    {}
    
    ~RNBOSubpatcher_05()
    {
        deallocateSignals();
    }
    
    Index getNumMidiInputPorts() const {
        return 1;
    }
    
    void processMidiEvent(MillisecondTime time, int port, ConstByteArray data, Index length) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->midiin_01_midihandler(data[0] & 240, (data[0] & 15) + 1, port, data, length);
    }
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        RNBO_UNUSED(numInputs);
        RNBO_UNUSED(inputs);
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
    
        if (this->getIsMuted())
            return;
    
        this->gen_01_perform(
            this->gen_01_in1,
            this->gen_01_stereo,
            this->gen_01_spray,
            this->gen_01_position,
            this->gen_01_density,
            this->gen_01_pitch,
            this->gen_01_spread,
            this->gen_01_grain_size,
            this->signals[0],
            this->signals[1],
            n
        );
    
        this->adsr_01_perform(
            this->adsr_01_attack,
            this->adsr_01_decay,
            this->adsr_01_sustain,
            this->adsr_01_release,
            this->zeroBuffer,
            this->signals[2],
            n
        );
    
        this->dspexpr_01_perform(this->signals[0], this->signals[2], this->signals[3], n);
        this->signaladder_01_perform(this->signals[3], out1, out1, n);
        this->signaladder_02_perform(this->signals[2], out3, out3, n);
        this->dspexpr_02_perform(this->signals[1], this->signals[2], this->signals[3], n);
        this->signaladder_03_perform(this->signals[3], out2, out2, n);
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        RNBO_ASSERT(this->_isInitialized);
    
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 4; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->adsr_01_triggerBuf = resizeSignal(this->adsr_01_triggerBuf, this->maxvs, maxBlockSize);
            this->adsr_01_triggerValueBuf = resizeSignal(this->adsr_01_triggerValueBuf, this->maxvs, maxBlockSize);
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->gen_01_dspsetup(forceDSPSetup);
        this->data_01_dspsetup(forceDSPSetup);
        this->adsr_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 0;
    }
    
    Index getNumOutputChannels() const {
        return 3;
    }
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("voice/message_obj-37") == objectId)
                this->message_01_listin_number_set(payload);
    
            if (TAG("voice/message_obj-32") == objectId)
                this->message_02_listin_number_set(payload);
    
            break;
            }
        }
    }
    
    void processListMessage(
        MessageTag tag,
        MessageTag objectId,
        MillisecondTime time,
        const list& payload
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("listin"):
            {
            if (TAG("voice/message_obj-37") == objectId)
                this->message_01_listin_list_set(payload);
    
            if (TAG("voice/message_obj-32") == objectId)
                this->message_02_listin_list_set(payload);
    
            break;
            }
        }
    }
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("bangin"):
            {
            if (TAG("voice/button_obj-39") == objectId)
                this->button_01_bangin_bang();
    
            break;
            }
        case TAG("listin"):
            {
            if (TAG("voice/message_obj-37") == objectId)
                this->message_01_listin_bang_bang();
    
            if (TAG("voice/message_obj-32") == objectId)
                this->message_02_listin_bang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("bangout"):
            {
            return "bangout";
            }
        case TAG("voice/button_obj-39"):
            {
            return "voice/button_obj-39";
            }
        case TAG("listout"):
            {
            return "listout";
            }
        case TAG("voice/message_obj-37"):
            {
            return "voice/message_obj-37";
            }
        case TAG("voice/message_obj-32"):
            {
            return "voice/message_obj-32";
            }
        case TAG("bangin"):
            {
            return "bangin";
            }
        case TAG("listin"):
            {
            return "listin";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 0;
    }
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        if (index == 0) {
            this->gen_01_sample = reInitDataView(this->gen_01_sample, this->getPatcher()->sample);
            this->data_01_buffer = reInitDataView(this->data_01_buffer, this->getPatcher()->sample);
            this->data_01_bufferUpdated();
        }
    }
    
    void initialize() {
        RNBO_ASSERT(!this->_isInitialized);
        this->assign_defaults();
        this->applyState();
        this->gen_01_sample = new Float32Buffer(this->getPatcher()->sample);
        this->data_01_buffer = new Float32Buffer(this->getPatcher()->sample);
        this->_isInitialized = true;
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_05* operator->() {
        return this;
    }
    const RNBOSubpatcher_05* operator->() const {
        return this;
    }
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -1468824490, false);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    Index voice() {
        return this->_voiceIndex;
    }
    
    number random(number low, number high) {
        number range = high - low;
        return globalrandom() * range + low;
    }
    
    template<typename BUFFERTYPE> number dim(BUFFERTYPE& buffer) {
        return buffer->getSize();
    }
    
    template<typename BUFFERTYPE> number channels(BUFFERTYPE& buffer) {
        return buffer->getChannels();
    }
    
    inline number intnum(const number value) {
        return trunc(value);
    }
    
    number mstosamps(MillisecondTime ms) {
        return ms * this->sr * 0.001;
    }
    
    number minimum(number x, number y) {
        return (y < x ? y : x);
    }
    
    number safepow(number base, number exponent) {
        return fixnan(rnbo_pow(base, exponent));
    }
    
    number scale(
        number x,
        number lowin,
        number hiin,
        number lowout,
        number highout,
        number pow
    ) {
        auto inscale = this->safediv(1., hiin - lowin);
        number outdiff = highout - lowout;
        number value = (x - lowin) * inscale;
    
        if (pow != 1) {
            if (value > 0)
                value = this->safepow(value, pow);
            else
                value = -this->safepow(-value, pow);
        }
    
        value = value * outdiff + lowout;
        return value;
    }
    
    inline number safemod(number f, number m) {
        if (m != 0) {
            Int f_trunc = (Int)(trunc(f));
            Int m_trunc = (Int)(trunc(m));
    
            if (f == f_trunc && m == m_trunc) {
                f = f_trunc % m_trunc;
            } else {
                if (m < 0) {
                    m = -m;
                }
    
                if (f >= m) {
                    if (f >= m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f -= m;
                    }
                } else if (f <= -m) {
                    if (f <= -m * 2.0) {
                        number d = f / m;
                        Int i = (Int)(trunc(d));
                        d = d - i;
                        f = d * m;
                    } else {
                        f += m;
                    }
                }
            }
        } else {
            f = 0.0;
        }
    
        return f;
    }
    
    number wrap(number x, number low, number high) {
        number lo;
        number hi;
    
        if (low == high)
            return low;
    
        if (low > high) {
            hi = low;
            lo = high;
        } else {
            lo = low;
            hi = high;
        }
    
        number range = hi - lo;
    
        if (x >= lo && x < hi)
            return x;
    
        if (range <= 0.000000001)
            return lo;
    
        Int numWraps = (Int)(trunc((x - lo) / range));
        numWraps = numWraps - ((x < lo ? 1 : 0));
        number result = x - range * numWraps;
    
        if (result >= hi)
            return result - range;
        else
            return result;
    }
    
    inline number linearinterp(number frac, number x, number y) {
        return x + (y - x) * frac;
    }
    
    inline number cubicinterp(number a, number w, number x, number y, number z) {
        number a1 = 1. + a;
        number aa = a * a1;
        number b = 1. - a;
        number b1 = 2. - a;
        number bb = b * b1;
        number fw = -.1666667 * bb * a;
        number fx = .5 * bb * a1;
        number fy = .5 * aa * b1;
        number fz = -.1666667 * aa * b;
        return w * fw + x * fx + y * fy + z * fz;
    }
    
    inline number fastcubicinterp(number a, number w, number x, number y, number z) {
        number a2 = a * a;
        number f0 = z - y - w + x;
        number f1 = w - x - f0;
        number f2 = y - w;
        number f3 = x;
        return f0 * a * a2 + f1 * a2 + f2 * a + f3;
    }
    
    inline number splineinterp(number a, number w, number x, number y, number z) {
        number a2 = a * a;
        number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
        number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
        number f2 = -0.5 * w + 0.5 * y;
        return f0 * a * a2 + f1 * a2 + f2 * a + x;
    }
    
    inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
        number ym2py2 = y0 + y4;
        number ym1py1 = y1 + y3;
        number y2mym2 = y4 - y0;
        number y1mym1 = y3 - y1;
        number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
        number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
        number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
        number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
        number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
        number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
        number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
        return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
    }
    
    inline number cosT8(number r) {
        number t84 = 56.0;
        number t83 = 1680.0;
        number t82 = 20160.0;
        number t81 = 2.4801587302e-05;
        number t73 = 42.0;
        number t72 = 840.0;
        number t71 = 1.9841269841e-04;
    
        if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
            number rr = r * r;
            return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
        } else if (r > 0.0) {
            r -= 1.57079632679489661923132169163975144;
            number rr = r * r;
            return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
        } else {
            r += 1.57079632679489661923132169163975144;
            number rr = r * r;
            return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
        }
    }
    
    inline number cosineinterp(number frac, number x, number y) {
        number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
        return x * (1.0 - a2) + y * a2;
    }
    
    template<typename BUFFERTYPE> array<SampleValue, 1 + 1> peek_boundmode_wrap_interp_cubic(BUFFERTYPE& buffer, SampleValue sampleIndex, Index channelOffset) {
        number bufferSize = buffer->getSize();
        const Index bufferChannels = (const Index)(buffer->getChannels());
        constexpr int ___N2 = 1 + 1;
        array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);
    
        if (bufferSize == 0 || (3 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
            return out;
        } else {
            {
                SampleValue bufferbindindex_result;
    
                {
                    {
                        {
                            bufferbindindex_result = this->wrap(sampleIndex, 0, bufferSize);
                        }
                    }
                }
    
                sampleIndex = bufferbindindex_result;
            }
    
            for (Index channel = 0; channel < 1; channel++) {
                Index channelIndex = (Index)(channel + channelOffset);
    
                {
                    if (channelIndex >= bufferChannels || channelIndex < 0) {
                        out[(Index)channel] = 0;
                        continue;
                    }
                }
    
                SampleValue bufferreadsample_result;
    
                {
                    auto& __buffer = buffer;
    
                    if (sampleIndex < 0.0) {
                        bufferreadsample_result = 0.0;
                    }
    
                    SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));
    
                    {
                        number frac = sampleIndex - truncIndex;
                        number wrap = bufferSize - 1;
    
                        {
                            {
                                SampleIndex index1 = (SampleIndex)(truncIndex - 1);
    
                                if (index1 < 0)
                                    index1 = wrap;
    
                                SampleIndex index2 = (SampleIndex)(index1 + 1);
    
                                if (index2 > wrap)
                                    index2 = 0;
    
                                SampleIndex index3 = (SampleIndex)(index2 + 1);
    
                                if (index3 > wrap)
                                    index3 = 0;
    
                                SampleIndex index4 = (SampleIndex)(index3 + 1);
    
                                if (index4 > wrap)
                                    index4 = 0;
    
                                bufferreadsample_result = this->cubicinterp(
                                    frac,
                                    __buffer->getSample(channelIndex, index1),
                                    __buffer->getSample(channelIndex, index2),
                                    __buffer->getSample(channelIndex, index3),
                                    __buffer->getSample(channelIndex, index4)
                                );
                            }
                        }
                    }
                }
    
                out[(Index)channel] = bufferreadsample_result;
            }
    
            out[1] = sampleIndex;
            return out;
        }
    }
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void eventinlet_01_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_01_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_density_set(converted);
        }
    }
    
    void eventinlet_02_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_02_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_grain_size_set(converted);
        }
    }
    
    void eventinlet_03_out1_bang_bang() {}
    
    void eventinlet_03_out1_number_set(number v) {
        this->gen_01_position_set(v);
    }
    
    void eventinlet_04_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_04_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_spread_set(converted);
        }
    }
    
    void eventinlet_05_out1_bang_bang() {}
    
    void eventinlet_05_out1_number_set(number v) {
        this->gen_01_spray_set(v);
    }
    
    void eventinlet_06_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_06_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_stereo_set(converted);
        }
    }
    
    void eventinlet_07_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_07_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->adsr_01_attack_set(converted);
        }
    }
    
    void eventinlet_08_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_08_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->adsr_01_decay_set(converted);
        }
    }
    
    void eventinlet_09_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_09_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->adsr_01_sustain_set(converted);
        }
    }
    
    void button_01_bangin_bang() {
        this->button_01_bangval_bang();
    }
    
    void eventinlet_10_out1_bang_bang() {
        this->intnum_01_value_bang();
    }
    
    void eventinlet_10_out1_number_set(number v) {
        this->intnum_01_value_set(v);
    }
    
    template<typename LISTTYPE> void eventinlet_10_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->intnum_01_value_set(converted);
        }
    }
    
    template<typename LISTTYPE> void message_01_listin_list_set(const LISTTYPE& v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_number_set(number v) {
        this->message_01_set_set(v);
    }
    
    void message_01_listin_bang_bang() {
        this->message_01_trigger_bang();
    }
    
    template<typename LISTTYPE> void message_02_listin_list_set(const LISTTYPE& v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_number_set(number v) {
        this->message_02_set_set(v);
    }
    
    void message_02_listin_bang_bang() {
        this->message_02_trigger_bang();
    }
    
    void eventinlet_11_out1_bang_bang() {}
    
    template<typename LISTTYPE> void eventinlet_11_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->adsr_01_release_set(converted);
        }
    }
    
    void adsr_01_mute_bang() {}
    
    void deallocateSignals() {
        Index i;
    
        for (i = 0; i < 4; i++) {
            this->signals[i] = freeSignal(this->signals[i]);
        }
    
        this->adsr_01_triggerBuf = freeSignal(this->adsr_01_triggerBuf);
        this->adsr_01_triggerValueBuf = freeSignal(this->adsr_01_triggerValueBuf);
        this->zeroBuffer = freeSignal(this->zeroBuffer);
        this->dummyBuffer = freeSignal(this->dummyBuffer);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {
        this->gen_01_noise_253_init();
        this->gen_01_counter_269_init();
        this->gen_01_latch_276_init();
        this->gen_01_latch_278_init();
        this->gen_01_counter_286_init();
        this->gen_01_noise_295_init();
        this->gen_01_noise_297_init();
        this->gen_01_latch_314_init();
        this->gen_01_latch_328_init();
        this->gen_01_noise_348_init();
        this->gen_01_counter_361_init();
        this->gen_01_latch_368_init();
        this->gen_01_latch_370_init();
        this->gen_01_counter_378_init();
        this->gen_01_noise_390_init();
        this->gen_01_noise_392_init();
        this->gen_01_latch_409_init();
        this->gen_01_latch_423_init();
        this->gen_01_noise_443_init();
        this->gen_01_counter_459_init();
        this->gen_01_latch_466_init();
        this->gen_01_latch_469_init();
        this->gen_01_counter_477_init();
        this->gen_01_noise_486_init();
        this->gen_01_noise_488_init();
        this->gen_01_latch_505_init();
        this->gen_01_latch_519_init();
        this->gen_01_noise_539_init();
        this->gen_01_counter_556_init();
        this->gen_01_latch_563_init();
        this->gen_01_latch_571_init();
        this->gen_01_counter_573_init();
        this->gen_01_noise_582_init();
        this->gen_01_noise_584_init();
        this->gen_01_latch_601_init();
        this->gen_01_latch_615_init();
        this->gen_01_noise_635_init();
        this->gen_01_counter_648_init();
        this->gen_01_latch_655_init();
        this->gen_01_latch_657_init();
        this->gen_01_counter_665_init();
        this->gen_01_noise_677_init();
        this->gen_01_noise_679_init();
        this->gen_01_latch_696_init();
        this->gen_01_latch_710_init();
        this->gen_01_noise_730_init();
        this->gen_01_counter_746_init();
        this->gen_01_latch_753_init();
        this->gen_01_latch_755_init();
        this->gen_01_counter_763_init();
        this->gen_01_noise_772_init();
        this->gen_01_noise_774_init();
        this->gen_01_latch_791_init();
        this->gen_01_latch_806_init();
        this->gen_01_noise_827_init();
        this->gen_01_counter_843_init();
        this->gen_01_latch_850_init();
        this->gen_01_latch_852_init();
        this->gen_01_counter_860_init();
        this->gen_01_noise_869_init();
        this->gen_01_noise_871_init();
        this->gen_01_latch_888_init();
        this->gen_01_latch_902_init();
        this->gen_01_noise_922_init();
        this->gen_01_counter_938_init();
        this->gen_01_latch_945_init();
        this->gen_01_latch_947_init();
        this->gen_01_counter_955_init();
        this->gen_01_noise_964_init();
        this->gen_01_noise_966_init();
        this->gen_01_latch_983_init();
        this->gen_01_latch_997_init();
        this->gen_01_noise_1017_init();
        this->gen_01_counter_1030_init();
        this->gen_01_latch_1037_init();
        this->gen_01_latch_1039_init();
        this->gen_01_counter_1047_init();
        this->gen_01_noise_1059_init();
        this->gen_01_noise_1061_init();
        this->gen_01_latch_1078_init();
        this->gen_01_latch_1092_init();
        this->gen_01_noise_1112_init();
        this->gen_01_counter_1128_init();
        this->gen_01_latch_1136_init();
        this->gen_01_latch_1144_init();
        this->gen_01_counter_1146_init();
        this->gen_01_noise_1155_init();
        this->gen_01_noise_1157_init();
        this->gen_01_latch_1174_init();
        this->gen_01_latch_1188_init();
        this->gen_01_noise_1208_init();
        this->gen_01_counter_1224_init();
        this->gen_01_latch_1231_init();
        this->gen_01_latch_1239_init();
        this->gen_01_counter_1241_init();
        this->gen_01_noise_1250_init();
        this->gen_01_noise_1252_init();
        this->gen_01_latch_1269_init();
        this->gen_01_latch_1284_init();
        this->gen_01_noise_1304_init();
        this->gen_01_counter_1320_init();
        this->gen_01_latch_1327_init();
        this->gen_01_latch_1335_init();
        this->gen_01_counter_1337_init();
        this->gen_01_noise_1346_init();
        this->gen_01_noise_1348_init();
        this->gen_01_latch_1365_init();
        this->gen_01_latch_1380_init();
        this->gen_01_noise_1401_init();
        this->gen_01_counter_1417_init();
        this->gen_01_latch_1424_init();
        this->gen_01_latch_1432_init();
        this->gen_01_counter_1434_init();
        this->gen_01_noise_1443_init();
        this->gen_01_noise_1445_init();
        this->gen_01_latch_1462_init();
        this->gen_01_latch_1476_init();
        this->gen_01_noise_1496_init();
        this->gen_01_counter_1512_init();
        this->gen_01_latch_1519_init();
        this->gen_01_latch_1527_init();
        this->gen_01_counter_1529_init();
        this->gen_01_noise_1538_init();
        this->gen_01_noise_1540_init();
        this->gen_01_latch_1557_init();
        this->gen_01_latch_1571_init();
        this->gen_01_noise_1591_init();
        this->gen_01_counter_1604_init();
        this->gen_01_latch_1611_init();
        this->gen_01_latch_1619_init();
        this->gen_01_counter_1621_init();
        this->gen_01_noise_1633_init();
        this->gen_01_noise_1635_init();
        this->gen_01_latch_1652_init();
        this->gen_01_latch_1667_init();
        this->gen_01_noise_1687_init();
        this->gen_01_counter_1700_init();
        this->gen_01_latch_1707_init();
        this->gen_01_latch_1710_init();
        this->gen_01_counter_1718_init();
        this->gen_01_noise_1730_init();
        this->gen_01_noise_1732_init();
        this->gen_01_latch_1749_init();
        this->gen_01_latch_1763_init();
        this->gen_01_noise_1783_init();
        this->gen_01_counter_1799_init();
        this->gen_01_latch_1806_init();
        this->gen_01_latch_1808_init();
        this->gen_01_counter_1816_init();
        this->gen_01_noise_1825_init();
        this->gen_01_noise_1827_init();
        this->gen_01_latch_1844_init();
        this->gen_01_latch_1858_init();
        this->gen_01_noise_1878_init();
        this->gen_01_counter_1894_init();
        this->gen_01_latch_1901_init();
        this->gen_01_latch_1903_init();
        this->gen_01_counter_1911_init();
        this->gen_01_noise_1920_init();
        this->gen_01_noise_1922_init();
        this->gen_01_latch_1939_init();
        this->gen_01_latch_1954_init();
        this->gen_01_noise_1975_init();
        this->gen_01_counter_1989_init();
        this->gen_01_latch_1996_init();
        this->gen_01_latch_1998_init();
        this->gen_01_counter_2006_init();
        this->gen_01_noise_2018_init();
        this->gen_01_noise_2020_init();
        this->gen_01_latch_2038_init();
        this->gen_01_latch_2052_init();
        this->gen_01_noise_2072_init();
        this->gen_01_counter_2086_init();
        this->gen_01_latch_2093_init();
        this->gen_01_latch_2095_init();
        this->gen_01_counter_2103_init();
        this->gen_01_noise_2115_init();
        this->gen_01_noise_2117_init();
        this->gen_01_latch_2134_init();
        this->gen_01_latch_2149_init();
        this->gen_01_noise_2169_init();
        this->gen_01_counter_2185_init();
        this->gen_01_latch_2192_init();
        this->gen_01_latch_2194_init();
        this->gen_01_counter_2202_init();
        this->gen_01_noise_2211_init();
        this->gen_01_noise_2213_init();
        this->gen_01_latch_2230_init();
        this->gen_01_latch_2244_init();
        this->gen_01_noise_2264_init();
        this->gen_01_counter_2280_init();
        this->gen_01_latch_2287_init();
        this->gen_01_latch_2289_init();
        this->gen_01_counter_2297_init();
        this->gen_01_noise_2306_init();
        this->gen_01_noise_2308_init();
        this->gen_01_latch_2325_init();
        this->gen_01_latch_2339_init();
        this->gen_01_noise_2359_init();
        this->gen_01_counter_2375_init();
        this->gen_01_latch_2382_init();
        this->gen_01_latch_2384_init();
        this->gen_01_counter_2392_init();
        this->gen_01_noise_2401_init();
        this->gen_01_noise_2403_init();
        this->gen_01_latch_2420_init();
        this->gen_01_latch_2434_init();
        this->gen_01_noise_2454_init();
        this->gen_01_counter_2470_init();
        this->gen_01_latch_2477_init();
        this->gen_01_latch_2486_init();
        this->gen_01_counter_2488_init();
        this->gen_01_noise_2497_init();
        this->gen_01_noise_2499_init();
        this->gen_01_latch_2516_init();
        this->gen_01_latch_2531_init();
        this->gen_01_noise_2551_init();
        this->gen_01_counter_2567_init();
        this->gen_01_latch_2574_init();
        this->gen_01_latch_2582_init();
        this->gen_01_counter_2584_init();
        this->gen_01_noise_2593_init();
        this->gen_01_noise_2595_init();
        this->gen_01_latch_2612_init();
        this->gen_01_latch_2626_init();
        this->gen_01_noise_2646_init();
        this->gen_01_counter_2660_init();
        this->gen_01_latch_2667_init();
        this->gen_01_latch_2669_init();
        this->gen_01_counter_2677_init();
        this->gen_01_noise_2689_init();
        this->gen_01_noise_2691_init();
        this->gen_01_latch_2708_init();
        this->gen_01_latch_2722_init();
        this->gen_01_noise_2742_init();
        this->gen_01_counter_2758_init();
        this->gen_01_latch_2765_init();
        this->gen_01_latch_2773_init();
        this->gen_01_counter_2775_init();
        this->gen_01_noise_2784_init();
        this->gen_01_noise_2786_init();
        this->gen_01_latch_2803_init();
        this->gen_01_latch_2817_init();
        this->gen_01_noise_2837_init();
        this->gen_01_counter_2853_init();
        this->gen_01_latch_2860_init();
        this->gen_01_latch_2868_init();
        this->gen_01_counter_2870_init();
        this->gen_01_noise_2879_init();
        this->gen_01_noise_2881_init();
        this->gen_01_latch_2898_init();
        this->gen_01_latch_2912_init();
        this->gen_01_noise_2932_init();
        this->gen_01_counter_2945_init();
        this->gen_01_latch_2952_init();
        this->gen_01_latch_2954_init();
        this->gen_01_counter_2962_init();
        this->gen_01_noise_2974_init();
        this->gen_01_noise_2976_init();
        this->gen_01_latch_2993_init();
        this->gen_01_latch_3007_init();
        this->gen_01_noise_3027_init();
        this->gen_01_counter_3043_init();
        this->gen_01_latch_3050_init();
        this->gen_01_latch_3058_init();
        this->gen_01_counter_3060_init();
        this->gen_01_noise_3069_init();
        this->gen_01_noise_3071_init();
        this->gen_01_latch_3088_init();
        this->gen_01_latch_3102_init();
        this->data_01_init();
        this->message_01_init();
        this->message_02_init();
    }
    
    void setVoiceIndex(Index index)  {
        this->_voiceIndex = index;
    }
    
    void setNoteNumber(Int noteNumber)  {
        this->_noteNumber = noteNumber;
    }
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double ) {}
    
    void extractState(PatcherStateInterface& ) {}
    
    void applyState() {}
    
    ParameterValue getPolyParameterValue(RNBOSubpatcher_05* voices, ParameterIndex index)  {
        switch (index) {
        default:
            {
            return voices[0]->getParameterValue(index);
            }
        }
    }
    
    void setPolyParameterValue(
        RNBOSubpatcher_05* voices,
        ParameterIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        switch (index) {
        default:
            {
            for (Index i = 0; i < 8; i++)
                voices[i]->setParameterValue(index, value, time);
            }
        }
    }
    
    void sendPolyParameter(ParameterIndex index, Index voiceIndex, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset + voiceIndex - 1, ignoreValue);
    }
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (index) {
        case -1468824490:
            {
            this->adsr_01_mute_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {}
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void allocateDataRefs() {
        this->gen_01_sample = this->gen_01_sample->allocateIfNeeded();
        this->data_01_buffer = this->data_01_buffer->allocateIfNeeded();
    }
    
    number gen_01_spread_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_01_spread_set(number v) {
        v = this->gen_01_spread_constrain(v);
        this->gen_01_spread = v;
    }
    
    void eventinlet_04_out1_number_set(number v) {
        this->gen_01_spread_set(v);
    }
    
    number gen_01_grain_size_constrain(number v) const {
        if (v < 10)
            v = 10;
    
        if (v > 500)
            v = 500;
    
        return v;
    }
    
    void gen_01_grain_size_set(number v) {
        v = this->gen_01_grain_size_constrain(v);
        this->gen_01_grain_size = v;
    }
    
    void eventinlet_02_out1_number_set(number v) {
        this->gen_01_grain_size_set(v);
    }
    
    number gen_01_density_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 60)
            v = 60;
    
        return v;
    }
    
    void gen_01_density_set(number v) {
        v = this->gen_01_density_constrain(v);
        this->gen_01_density = v;
    }
    
    void eventinlet_01_out1_number_set(number v) {
        this->gen_01_density_set(v);
    }
    
    number gen_01_stereo_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_01_stereo_set(number v) {
        v = this->gen_01_stereo_constrain(v);
        this->gen_01_stereo = v;
    }
    
    void eventinlet_06_out1_number_set(number v) {
        this->gen_01_stereo_set(v);
    }
    
    void adsr_01_release_set(number v) {
        this->adsr_01_release = v;
    }
    
    void eventinlet_11_out1_number_set(number v) {
        this->adsr_01_release_set(v);
    }
    
    void adsr_01_sustain_set(number v) {
        this->adsr_01_sustain = v;
    }
    
    void eventinlet_09_out1_number_set(number v) {
        this->adsr_01_sustain_set(v);
    }
    
    void adsr_01_decay_set(number v) {
        this->adsr_01_decay = v;
    }
    
    void eventinlet_08_out1_number_set(number v) {
        this->adsr_01_decay_set(v);
    }
    
    void adsr_01_attack_set(number v) {
        this->adsr_01_attack = v;
    }
    
    void eventinlet_07_out1_number_set(number v) {
        this->adsr_01_attack_set(v);
    }
    
    number gen_01_spray_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_01_spray_set(number v) {
        v = this->gen_01_spray_constrain(v);
        this->gen_01_spray = v;
    }
    
    template<typename LISTTYPE> void eventinlet_05_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_spray_set(converted);
        }
    }
    
    number gen_01_position_constrain(number v) const {
        if (v < 0)
            v = 0;
    
        if (v > 1)
            v = 1;
    
        return v;
    }
    
    void gen_01_position_set(number v) {
        v = this->gen_01_position_constrain(v);
        this->gen_01_position = v;
    }
    
    template<typename LISTTYPE> void eventinlet_03_out1_list_set(const LISTTYPE& v) {
        {
            number converted = (v->length > 0 ? v[0] : 0);
            this->gen_01_position_set(converted);
        }
    }
    
    template<typename LISTTYPE> void message_02_set_set(const LISTTYPE& v) {
        this->message_02_set = jsCreateListCopy(v);
    }
    
    void expr_02_in2_set(number v) {
        this->expr_02_in2 = v;
    }
    
    void intnum_01_out_set(number v) {
        {
            listbase<number, 1> converted = {v};
            this->message_02_set_set(converted);
        }
    
        this->expr_02_in2_set(v);
    }
    
    void intnum_01_input_bang_bang() {
        this->intnum_01_out_set(trunc(this->intnum_01_stored));
    }
    
    void button_01_output_bang() {
        this->intnum_01_input_bang_bang();
    }
    
    void button_01_bangval_bang() {
        ;
        this->button_01_output_bang();
    }
    
    void intnum_01_value_bang() {
        number v = this->intnum_01_value;
        this->intnum_01_stored = v;
    }
    
    void intnum_01_value_set(number v) {
        this->intnum_01_value = v;
        this->intnum_01_stored = v;
    }
    
    template<typename LISTTYPE> void message_01_set_set(const LISTTYPE& v) {
        this->message_01_set = jsCreateListCopy(v);
    }
    
    template<typename LISTTYPE> void message_01_out_set(const LISTTYPE& ) {}
    
    void message_01_trigger_bang() {
        if ((bool)(this->message_01_set->length) || (bool)(false)) {
            this->message_01_out_set(this->message_01_set);
        }
    }
    
    template<typename LISTTYPE> void message_02_out_set(const LISTTYPE& ) {}
    
    void message_02_trigger_bang() {
        if ((bool)(this->message_02_set->length) || (bool)(false)) {
            this->message_02_out_set(this->message_02_set);
        }
    }
    
    void midiparse_01_channel_set(number ) {}
    
    void adsr_01_trigger_number_set(number v) {
        this->adsr_01_trigger_number = v;
    
        if (v != 0)
            this->adsr_01_triggerBuf[this->sampleOffsetIntoNextAudioBuffer] = 1;
    
        for (number i = this->sampleOffsetIntoNextAudioBuffer; i < this->vs; i++) {
            this->adsr_01_triggerValueBuf[(Index)i] = v;
        }
    }
    
    void expr_01_out1_set(number v) {
        this->expr_01_out1 = v;
        this->adsr_01_trigger_number_set(this->expr_01_out1);
    }
    
    void expr_01_in1_set(number in1) {
        this->expr_01_in1 = in1;
    
        this->expr_01_out1_set(
            (this->expr_01_in2 == 0 ? 0 : (this->expr_01_in2 == 0. ? 0. : this->expr_01_in1 / this->expr_01_in2))
        );//#map:voice//_obj-19:1
    }
    
    void unpack_01_out2_set(number v) {
        this->unpack_01_out2 = v;
        this->expr_01_in1_set(v);
    }
    
    void trigger_01_out2_bang() {
        this->button_01_bangval_bang();
    }
    
    number gen_01_pitch_constrain(number v) const {
        if (v < -60)
            v = -60;
    
        if (v > 60)
            v = 60;
    
        return v;
    }
    
    void gen_01_pitch_set(number v) {
        v = this->gen_01_pitch_constrain(v);
        this->gen_01_pitch = v;
    }
    
    void expr_02_out1_set(number v) {
        this->expr_02_out1 = v;
    
        {
            listbase<number, 1> converted = {this->expr_02_out1};
            this->message_01_set_set(converted);
        }
    
        this->gen_01_pitch_set(this->expr_02_out1);
    }
    
    void expr_02_in1_set(number in1) {
        this->expr_02_in1 = in1;
        this->expr_02_out1_set(this->expr_02_in1 - this->expr_02_in2);//#map:voice/-_obj-31:1
    }
    
    void trigger_01_out1_set(number v) {
        this->expr_02_in1_set(v);
    }
    
    void trigger_01_input_number_set(number v) {
        this->trigger_01_out2_bang();
        this->trigger_01_out1_set(trunc(v));
    }
    
    void expr_03_out1_set(number v) {
        this->expr_03_out1 = v;
        this->trigger_01_input_number_set(this->expr_03_out1);
    }
    
    void expr_03_in1_set(number in1) {
        this->expr_03_in1 = in1;
        this->expr_03_out1_set(this->expr_03_in1 - this->expr_03_in2);//#map:voice/-_obj-3:1
    }
    
    void unpack_01_out1_set(number v) {
        this->unpack_01_out1 = v;
        this->expr_03_in1_set(v);
    }
    
    template<typename LISTTYPE> void unpack_01_input_list_set(const LISTTYPE& v) {
        if (v->length > 1)
            this->unpack_01_out2_set(v[1]);
    
        if (v->length > 0)
            this->unpack_01_out1_set(v[0]);
    }
    
    template<typename LISTTYPE> void midiparse_01_noteonoroff_set(const LISTTYPE& v) {
        this->unpack_01_input_list_set(v);
    }
    
    template<typename LISTTYPE> void midiparse_01_polypressure_set(const LISTTYPE& ) {}
    
    template<typename LISTTYPE> void midiparse_01_controlchange_set(const LISTTYPE& ) {}
    
    void midiparse_01_programchange_set(number ) {}
    
    void midiparse_01_aftertouch_set(number ) {}
    
    void midiparse_01_pitchbend_set(number ) {}
    
    void midiparse_01_midiin_set(number midivalue) {
        list result = this->midiparse_01_parser_next(midivalue);
    
        switch ((int)result[0]) {
        case 0:
            {
            this->midiparse_01_channel_set(result[3]);
            this->midiparse_01_noteonoroff_set(listbase<number, 2>{result[1], result[2]});
            break;
            }
        case 1:
            {
            this->midiparse_01_channel_set(result[3]);
            this->midiparse_01_polypressure_set(listbase<number, 2>{result[1], result[2]});
            break;
            }
        case 2:
            {
            this->midiparse_01_channel_set(result[3]);
            this->midiparse_01_controlchange_set(listbase<number, 2>{result[1], result[2]});
            break;
            }
        case 3:
            {
            this->midiparse_01_channel_set(result[2]);
            this->midiparse_01_programchange_set(result[1]);
            break;
            }
        case 4:
            {
            this->midiparse_01_channel_set(result[2]);
            this->midiparse_01_aftertouch_set(result[1]);
            break;
            }
        case 5:
            {
            this->midiparse_01_channel_set(result[2]);
            this->midiparse_01_pitchbend_set(result[1]);
            break;
            }
        }
    }
    
    void midiin_01_midiout_set(number v) {
        this->midiparse_01_midiin_set(v);
    }
    
    void midiin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
        RNBO_UNUSED(port);
        RNBO_UNUSED(channel);
        RNBO_UNUSED(status);
        Index i;
    
        for (i = 0; i < length; i++) {
            this->midiin_01_midiout_set(data[i]);
        }
    }
    
    void midiouthelper_midiout_set(number ) {}
    
    void gen_01_perform(
        number in1,
        number stereo,
        number spray,
        number position,
        number density,
        number pitch,
        number spread,
        number grain_size,
        SampleValue * out1,
        SampleValue * out2,
        Index n
    ) {
        RNBO_UNUSED(in1);
        auto sample_dim_1_0 = this->dim(this->gen_01_sample);
        auto sample_chans_2_1 = this->channels(this->gen_01_sample);
        auto int_3_2 = this->intnum(1);
        auto int_4_3 = this->intnum(2);
        auto int_5_4 = this->intnum(3);
        auto int_6_5 = this->intnum(4);
        auto int_7_6 = this->intnum(9);
        number Spy_8_7 = spray;
        number Spy_9_8 = Spy_8_7;
        number Spy_10_9 = Spy_8_7;
        number Spy_11_10 = Spy_8_7;
        number Spy_12_11 = Spy_8_7;
        auto int_13_12 = this->intnum(8);
        number Spy_14_13 = Spy_8_7;
        auto int_15_14 = this->intnum(7);
        number Spy_16_15 = Spy_8_7;
        auto int_17_16 = this->intnum(6);
        number P_18_17 = pitch;
        number P_19_18 = P_18_17;
        number P_20_19 = P_18_17;
        number P_21_20 = P_18_17;
        number P_22_21 = P_18_17;
        number P_23_22 = P_18_17;
        number P_24_23 = P_18_17;
        number P_25_24 = P_18_17;
        number Spy_26_25 = Spy_8_7;
        auto int_27_26 = this->intnum(5);
        number P_28_27 = P_18_17;
        number Spy_29_28 = Spy_8_7;
        auto int_30_29 = this->intnum(14);
        number P_31_30 = P_18_17;
        number Spd_32_31 = spread;
        number Spd_33_32 = Spd_32_31;
        number Spd_34_33 = Spd_32_31;
        number Spd_35_34 = Spd_32_31;
        number Spd_36_35 = Spd_32_31;
        number Spd_37_36 = Spd_32_31;
        number Spd_38_37 = Spd_32_31;
        number Spd_39_38 = Spd_32_31;
        number Spd_40_39 = Spd_32_31;
        number Spd_41_40 = Spd_32_31;
        number Spy_42_41 = Spy_8_7;
        auto int_43_42 = this->intnum(13);
        number D_44_43 = density;
        number D_45_44 = D_44_43;
        number D_46_45 = D_44_43;
        number D_47_46 = D_44_43;
        number D_48_47 = D_44_43;
        number D_49_48 = D_44_43;
        number D_50_49 = D_44_43;
        number D_51_50 = D_44_43;
        number D_52_51 = D_44_43;
        number D_53_52 = D_44_43;
        number D_54_53 = D_44_43;
        number P_55_54 = P_18_17;
        number Spd_56_55 = Spd_32_31;
        number Spy_57_56 = Spy_8_7;
        auto int_58_57 = this->intnum(12);
        number D_59_58 = D_44_43;
        number P_60_59 = P_18_17;
        number Spd_61_60 = Spd_32_31;
        number Spy_62_61 = Spy_8_7;
        auto int_63_62 = this->intnum(11);
        number D_64_63 = D_44_43;
        number GS_65_64 = grain_size;
        number GS_66_65 = GS_65_64;
        number GS_67_66 = GS_65_64;
        number GS_68_67 = GS_65_64;
        number GS_69_68 = GS_65_64;
        number GS_70_69 = GS_65_64;
        number GS_71_70 = GS_65_64;
        number GS_72_71 = GS_65_64;
        number GS_73_72 = GS_65_64;
        number GS_74_73 = GS_65_64;
        number GS_75_74 = GS_65_64;
        number GS_76_75 = GS_65_64;
        number GS_77_76 = GS_65_64;
        number P_78_77 = P_18_17;
        number Spd_79_78 = Spd_32_31;
        number Spy_80_79 = Spy_8_7;
        auto int_81_80 = this->intnum(10);
        number D_82_81 = D_44_43;
        number GS_83_82 = GS_65_64;
        number P_84_83 = P_18_17;
        number Spd_85_84 = Spd_32_31;
        number Spy_86_85 = Spy_8_7;
        auto int_87_86 = this->intnum(29);
        number D_88_87 = D_44_43;
        number GS_89_88 = GS_65_64;
        number P_90_89 = P_18_17;
        number Spd_91_90 = Spd_32_31;
        number Spy_92_91 = Spy_8_7;
        auto int_93_92 = this->intnum(0);
        number D_94_93 = D_44_43;
        number GS_95_94 = GS_65_64;
        number P_96_95 = P_18_17;
        number Spd_97_96 = Spd_32_31;
        number Spy_98_97 = Spy_8_7;
        auto int_99_98 = this->intnum(28);
        number D_100_99 = D_44_43;
        number GS_101_100 = GS_65_64;
        number P_102_101 = P_18_17;
        number Spd_103_102 = Spd_32_31;
        number Spy_104_103 = Spy_8_7;
        auto int_105_104 = this->intnum(27);
        number D_106_105 = D_44_43;
        number GS_107_106 = GS_65_64;
        number P_108_107 = P_18_17;
        number Spd_109_108 = Spd_32_31;
        number Spy_110_109 = Spy_8_7;
        auto int_111_110 = this->intnum(26);
        number D_112_111 = D_44_43;
        number GS_113_112 = GS_65_64;
        number P_114_113 = P_18_17;
        number Spd_115_114 = Spd_32_31;
        number Spy_116_115 = Spy_8_7;
        auto int_117_116 = this->intnum(25);
        number D_118_117 = D_44_43;
        number GS_119_118 = GS_65_64;
        number P_120_119 = P_18_17;
        number Spd_121_120 = Spd_32_31;
        number Spy_122_121 = Spy_8_7;
        number St_123_122 = stereo;
        number St_124_123 = St_123_122;
        number St_125_124 = St_123_122;
        number St_126_125 = St_123_122;
        number St_127_126 = St_123_122;
        number St_128_127 = St_123_122;
        number St_129_128 = St_123_122;
        number St_130_129 = St_123_122;
        number St_131_130 = St_123_122;
        number St_132_131 = St_123_122;
        number St_133_132 = St_123_122;
        number St_134_133 = St_123_122;
        number St_135_134 = St_123_122;
        number St_136_135 = St_123_122;
        number St_137_136 = St_123_122;
        number St_138_137 = St_123_122;
        number St_139_138 = St_123_122;
        number St_140_139 = St_123_122;
        number St_141_140 = St_123_122;
        number St_142_141 = St_123_122;
        auto int_143_142 = this->intnum(24);
        number D_144_143 = D_44_43;
        number GS_145_144 = GS_65_64;
        number P_146_145 = P_18_17;
        number Spd_147_146 = Spd_32_31;
        number Spy_148_147 = Spy_8_7;
        number St_149_148 = St_123_122;
        auto int_150_149 = this->intnum(23);
        number D_151_150 = D_44_43;
        number GS_152_151 = GS_65_64;
        number P_153_152 = P_18_17;
        number Spd_154_153 = Spd_32_31;
        number Spy_155_154 = Spy_8_7;
        number St_156_155 = St_123_122;
        auto int_157_156 = this->intnum(22);
        number D_158_157 = D_44_43;
        number GS_159_158 = GS_65_64;
        number P_160_159 = P_18_17;
        number Spd_161_160 = Spd_32_31;
        number Spy_162_161 = Spy_8_7;
        number St_163_162 = St_123_122;
        auto int_164_163 = this->intnum(21);
        number D_165_164 = D_44_43;
        number GS_166_165 = GS_65_64;
        number P_167_166 = P_18_17;
        number Spd_168_167 = Spd_32_31;
        number Spy_169_168 = Spy_8_7;
        number St_170_169 = St_123_122;
        auto int_171_170 = this->intnum(20);
        number D_172_171 = D_44_43;
        number GS_173_172 = GS_65_64;
        number P_174_173 = P_18_17;
        number Spd_175_174 = Spd_32_31;
        number Pos_176_175 = position;
        number Pos_177_176 = Pos_176_175;
        number Pos_178_177 = Pos_176_175;
        number Pos_179_178 = Pos_176_175;
        number Pos_180_179 = Pos_176_175;
        number Pos_181_180 = Pos_176_175;
        number Pos_182_181 = Pos_176_175;
        number Pos_183_182 = Pos_176_175;
        number Pos_184_183 = Pos_176_175;
        number Pos_185_184 = Pos_176_175;
        number Pos_186_185 = Pos_176_175;
        number Pos_187_186 = Pos_176_175;
        number Pos_188_187 = Pos_176_175;
        number Pos_189_188 = Pos_176_175;
        number Pos_190_189 = Pos_176_175;
        number Pos_191_190 = Pos_176_175;
        number Pos_192_191 = Pos_176_175;
        number Pos_193_192 = Pos_176_175;
        number Pos_194_193 = Pos_176_175;
        number Pos_195_194 = Pos_176_175;
        number Pos_196_195 = Pos_176_175;
        number Pos_197_196 = Pos_176_175;
        number Pos_198_197 = Pos_176_175;
        number Pos_199_198 = Pos_176_175;
        number Pos_200_199 = Pos_176_175;
        number Spy_201_200 = Spy_8_7;
        number St_202_201 = St_123_122;
        auto int_203_202 = this->intnum(19);
        number D_204_203 = D_44_43;
        number GS_205_204 = GS_65_64;
        number P_206_205 = P_18_17;
        number Spd_207_206 = Spd_32_31;
        number Pos_208_207 = Pos_176_175;
        number Spy_209_208 = Spy_8_7;
        number St_210_209 = St_123_122;
        auto int_211_210 = this->intnum(18);
        number D_212_211 = D_44_43;
        number GS_213_212 = GS_65_64;
        number P_214_213 = P_18_17;
        number Spd_215_214 = Spd_32_31;
        number Pos_216_215 = Pos_176_175;
        number Spy_217_216 = Spy_8_7;
        number St_218_217 = St_123_122;
        auto int_219_218 = this->intnum(17);
        number D_220_219 = D_44_43;
        number GS_221_220 = GS_65_64;
        number P_222_221 = P_18_17;
        number Spd_223_222 = Spd_32_31;
        number Pos_224_223 = Pos_176_175;
        number Spy_225_224 = Spy_8_7;
        number St_226_225 = St_123_122;
        auto int_227_226 = this->intnum(16);
        number D_228_227 = D_44_43;
        number GS_229_228 = GS_65_64;
        number P_230_229 = P_18_17;
        number Spd_231_230 = Spd_32_31;
        number Pos_232_231 = Pos_176_175;
        number Spy_233_232 = Spy_8_7;
        number St_234_233 = St_123_122;
        auto int_235_234 = this->intnum(15);
        number D_236_235 = D_44_43;
        number GS_237_236 = GS_65_64;
        number P_238_237 = P_18_17;
        number Spd_239_238 = Spd_32_31;
        number Pos_240_239 = Pos_176_175;
        number Spy_241_240 = Spy_8_7;
        number St_242_241 = St_123_122;
        number Rst_243_242 = 0;
        number gen_244_243 = 0;
        auto sample_dim_245_244 = this->dim(this->gen_01_sample);
        auto sample_chans_246_245 = this->channels(this->gen_01_sample);
        number clamp_248_247 = (int_81_80 > 29 ? 29 : (int_81_80 < 0 ? 0 : int_81_80));
        auto int_249_248 = this->intnum(30);
        number clamp_250_249 = (St_137_136 > 1 ? 1 : (St_137_136 < 0 ? 0 : St_137_136));
        auto int_253_255 = this->intnum(1);
        number clamp_254_256 = (GS_83_82 > 500 ? 500 : (GS_83_82 < 10 ? 10 : GS_83_82));
        auto mstosamps_255_257 = this->mstosamps(clamp_254_256);
        auto int_256_258 = this->intnum(2);
        auto int_257_259 = this->intnum(2);
        number clamp_258_260 = (Pos_190_189 > 1 ? 1 : (Pos_190_189 < 0 ? 0 : Pos_190_189));
        number clamp_259_261 = (D_82_81 > 60 ? 60 : (D_82_81 < 0 ? 0 : D_82_81));
        number clamp_292_300 = (Spy_86_85 > 1 ? 1 : (Spy_86_85 < 0 ? 0 : Spy_86_85));
        auto dim_295_304 = this->dim(this->gen_01_sample);
        number div_296_305 = dim_295_304 / (number)2;
        number div_297_306 = clamp_254_256 / (number)2;
        auto mstosamps_298_307 = this->mstosamps(div_297_306);
        number sub_299_308 = div_296_305 - mstosamps_298_307;
        auto scale_301_310 = this->scale(clamp_258_260, 0, 1, 0, sub_299_308, 1);
        number clamp_305_316 = (Spd_85_84 > 1 ? 1 : (Spd_85_84 < 0 ? 0 : Spd_85_84));
        number clamp_309_321 = (P_84_83 > 60 ? 60 : (P_84_83 < -60 ? -60 : P_84_83));
        number Rst_325_338 = Rst_243_242;
        number gen_326_339 = 0;
        auto sample_dim_327_340 = this->dim(this->gen_01_sample);
        auto sample_chans_328_341 = this->channels(this->gen_01_sample);
        number clamp_330_343 = (int_3_2 > 29 ? 29 : (int_3_2 < 0 ? 0 : int_3_2));
        auto int_331_344 = this->intnum(30);
        number clamp_332_345 = (St_124_123 > 1 ? 1 : (St_124_123 < 0 ? 0 : St_124_123));
        auto int_335_350 = this->intnum(1);
        number clamp_336_351 = (GS_66_65 > 500 ? 500 : (GS_66_65 < 10 ? 10 : GS_66_65));
        auto mstosamps_337_352 = this->mstosamps(clamp_336_351);
        number clamp_338_353 = (D_45_44 > 60 ? 60 : (D_45_44 < 0 ? 0 : D_45_44));
        auto int_368_387 = this->intnum(2);
        auto int_369_388 = this->intnum(2);
        number clamp_370_389 = (Pos_177_176 > 1 ? 1 : (Pos_177_176 < 0 ? 0 : Pos_177_176));
        number clamp_374_395 = (Spy_9_8 > 1 ? 1 : (Spy_9_8 < 0 ? 0 : Spy_9_8));
        auto dim_377_399 = this->dim(this->gen_01_sample);
        number div_378_400 = dim_377_399 / (number)2;
        number div_379_401 = clamp_336_351 / (number)2;
        auto mstosamps_380_402 = this->mstosamps(div_379_401);
        number sub_381_403 = div_378_400 - mstosamps_380_402;
        auto scale_383_405 = this->scale(clamp_370_389, 0, 1, 0, sub_381_403, 1);
        number clamp_387_411 = (Spd_33_32 > 1 ? 1 : (Spd_33_32 < 0 ? 0 : Spd_33_32));
        number clamp_391_416 = (P_19_18 > 60 ? 60 : (P_19_18 < -60 ? -60 : P_19_18));
        number Rst_407_433 = Rst_243_242;
        number gen_408_434 = 0;
        auto sample_dim_409_435 = this->dim(this->gen_01_sample);
        auto sample_chans_410_436 = this->channels(this->gen_01_sample);
        number clamp_412_438 = (int_4_3 > 29 ? 29 : (int_4_3 < 0 ? 0 : int_4_3));
        auto int_413_439 = this->intnum(30);
        number clamp_414_440 = (St_125_124 > 1 ? 1 : (St_125_124 < 0 ? 0 : St_125_124));
        auto int_417_445 = this->intnum(1);
        number clamp_418_446 = (GS_67_66 > 500 ? 500 : (GS_67_66 < 10 ? 10 : GS_67_66));
        auto mstosamps_419_447 = this->mstosamps(clamp_418_446);
        auto int_420_448 = this->intnum(2);
        auto int_421_449 = this->intnum(2);
        number clamp_422_450 = (Pos_178_177 > 1 ? 1 : (Pos_178_177 < 0 ? 0 : Pos_178_177));
        number clamp_423_451 = (D_46_45 > 60 ? 60 : (D_46_45 < 0 ? 0 : D_46_45));
        number clamp_456_491 = (Spy_10_9 > 1 ? 1 : (Spy_10_9 < 0 ? 0 : Spy_10_9));
        auto dim_459_495 = this->dim(this->gen_01_sample);
        number div_460_496 = dim_459_495 / (number)2;
        number div_461_497 = clamp_418_446 / (number)2;
        auto mstosamps_462_498 = this->mstosamps(div_461_497);
        number sub_463_499 = div_460_496 - mstosamps_462_498;
        auto scale_465_501 = this->scale(clamp_422_450, 0, 1, 0, sub_463_499, 1);
        number clamp_469_507 = (Spd_34_33 > 1 ? 1 : (Spd_34_33 < 0 ? 0 : Spd_34_33));
        number clamp_473_512 = (P_20_19 > 60 ? 60 : (P_20_19 < -60 ? -60 : P_20_19));
        number Rst_489_529 = Rst_243_242;
        auto sample_dim_490_530 = this->dim(this->gen_01_sample);
        auto sample_chans_491_531 = this->channels(this->gen_01_sample);
        number gen_492_532 = 0;
        number clamp_494_534 = (int_5_4 > 29 ? 29 : (int_5_4 < 0 ? 0 : int_5_4));
        auto int_495_535 = this->intnum(30);
        number clamp_496_536 = (St_126_125 > 1 ? 1 : (St_126_125 < 0 ? 0 : St_126_125));
        auto int_499_541 = this->intnum(1);
        number clamp_500_542 = (GS_68_67 > 500 ? 500 : (GS_68_67 < 10 ? 10 : GS_68_67));
        auto mstosamps_501_543 = this->mstosamps(clamp_500_542);
        auto int_502_544 = this->intnum(2);
        auto int_503_545 = this->intnum(2);
        number clamp_504_546 = (Pos_179_178 > 1 ? 1 : (Pos_179_178 < 0 ? 0 : Pos_179_178));
        number clamp_505_547 = (D_47_46 > 60 ? 60 : (D_47_46 < 0 ? 0 : D_47_46));
        number clamp_538_587 = (Spy_11_10 > 1 ? 1 : (Spy_11_10 < 0 ? 0 : Spy_11_10));
        auto dim_541_591 = this->dim(this->gen_01_sample);
        number div_542_592 = dim_541_591 / (number)2;
        number div_543_593 = clamp_500_542 / (number)2;
        auto mstosamps_544_594 = this->mstosamps(div_543_593);
        number sub_545_595 = div_542_592 - mstosamps_544_594;
        auto scale_547_597 = this->scale(clamp_504_546, 0, 1, 0, sub_545_595, 1);
        number clamp_551_603 = (Spd_35_34 > 1 ? 1 : (Spd_35_34 < 0 ? 0 : Spd_35_34));
        number clamp_555_608 = (P_21_20 > 60 ? 60 : (P_21_20 < -60 ? -60 : P_21_20));
        number Rst_571_625 = Rst_243_242;
        number gen_572_626 = 0;
        auto sample_dim_573_627 = this->dim(this->gen_01_sample);
        auto sample_chans_574_628 = this->channels(this->gen_01_sample);
        number clamp_576_630 = (int_6_5 > 29 ? 29 : (int_6_5 < 0 ? 0 : int_6_5));
        auto int_577_631 = this->intnum(30);
        number clamp_578_632 = (St_127_126 > 1 ? 1 : (St_127_126 < 0 ? 0 : St_127_126));
        auto int_581_637 = this->intnum(1);
        number clamp_582_638 = (GS_69_68 > 500 ? 500 : (GS_69_68 < 10 ? 10 : GS_69_68));
        auto mstosamps_583_639 = this->mstosamps(clamp_582_638);
        number clamp_584_640 = (D_48_47 > 60 ? 60 : (D_48_47 < 0 ? 0 : D_48_47));
        auto int_614_674 = this->intnum(2);
        auto int_615_675 = this->intnum(2);
        number clamp_616_676 = (Pos_180_179 > 1 ? 1 : (Pos_180_179 < 0 ? 0 : Pos_180_179));
        number clamp_620_682 = (Spy_12_11 > 1 ? 1 : (Spy_12_11 < 0 ? 0 : Spy_12_11));
        auto dim_623_686 = this->dim(this->gen_01_sample);
        number div_624_687 = dim_623_686 / (number)2;
        number div_625_688 = clamp_582_638 / (number)2;
        auto mstosamps_626_689 = this->mstosamps(div_625_688);
        number sub_627_690 = div_624_687 - mstosamps_626_689;
        auto scale_629_692 = this->scale(clamp_616_676, 0, 1, 0, sub_627_690, 1);
        number clamp_633_698 = (Spd_36_35 > 1 ? 1 : (Spd_36_35 < 0 ? 0 : Spd_36_35));
        number clamp_637_703 = (P_22_21 > 60 ? 60 : (P_22_21 < -60 ? -60 : P_22_21));
        number Rst_653_720 = Rst_243_242;
        auto sample_dim_654_721 = this->dim(this->gen_01_sample);
        auto sample_chans_655_722 = this->channels(this->gen_01_sample);
        number gen_656_723 = 0;
        number clamp_658_725 = (int_7_6 > 29 ? 29 : (int_7_6 < 0 ? 0 : int_7_6));
        auto int_659_726 = this->intnum(30);
        number clamp_660_727 = (St_128_127 > 1 ? 1 : (St_128_127 < 0 ? 0 : St_128_127));
        auto int_663_732 = this->intnum(1);
        number clamp_664_733 = (GS_70_69 > 500 ? 500 : (GS_70_69 < 10 ? 10 : GS_70_69));
        auto mstosamps_665_734 = this->mstosamps(clamp_664_733);
        auto int_666_735 = this->intnum(2);
        auto int_667_736 = this->intnum(2);
        number clamp_668_737 = (Pos_181_180 > 1 ? 1 : (Pos_181_180 < 0 ? 0 : Pos_181_180));
        number clamp_669_738 = (D_49_48 > 60 ? 60 : (D_49_48 < 0 ? 0 : D_49_48));
        number clamp_702_777 = (Spy_8_7 > 1 ? 1 : (Spy_8_7 < 0 ? 0 : Spy_8_7));
        auto dim_705_781 = this->dim(this->gen_01_sample);
        number div_706_782 = dim_705_781 / (number)2;
        number div_707_783 = clamp_664_733 / (number)2;
        auto mstosamps_708_784 = this->mstosamps(div_707_783);
        number sub_709_785 = div_706_782 - mstosamps_708_784;
        auto scale_711_787 = this->scale(clamp_668_737, 0, 1, 0, sub_709_785, 1);
        number clamp_715_793 = (Spd_37_36 > 1 ? 1 : (Spd_37_36 < 0 ? 0 : Spd_37_36));
        number clamp_719_799 = (P_23_22 > 60 ? 60 : (P_23_22 < -60 ? -60 : P_23_22));
        number Rst_735_816 = Rst_243_242;
        auto sample_dim_736_817 = this->dim(this->gen_01_sample);
        auto sample_chans_737_818 = this->channels(this->gen_01_sample);
        number gen_738_819 = 0;
        number clamp_740_821 = (int_13_12 > 29 ? 29 : (int_13_12 < 0 ? 0 : int_13_12));
        auto int_741_822 = this->intnum(30);
        number clamp_742_823 = (St_129_128 > 1 ? 1 : (St_129_128 < 0 ? 0 : St_129_128));
        auto int_745_829 = this->intnum(1);
        number clamp_746_830 = (GS_71_70 > 500 ? 500 : (GS_71_70 < 10 ? 10 : GS_71_70));
        auto mstosamps_747_831 = this->mstosamps(clamp_746_830);
        auto int_748_832 = this->intnum(2);
        auto int_749_833 = this->intnum(2);
        number clamp_750_834 = (Pos_182_181 > 1 ? 1 : (Pos_182_181 < 0 ? 0 : Pos_182_181));
        number clamp_751_835 = (D_50_49 > 60 ? 60 : (D_50_49 < 0 ? 0 : D_50_49));
        number clamp_784_874 = (Spy_14_13 > 1 ? 1 : (Spy_14_13 < 0 ? 0 : Spy_14_13));
        auto dim_787_878 = this->dim(this->gen_01_sample);
        number div_788_879 = dim_787_878 / (number)2;
        number div_789_880 = clamp_746_830 / (number)2;
        auto mstosamps_790_881 = this->mstosamps(div_789_880);
        number sub_791_882 = div_788_879 - mstosamps_790_881;
        auto scale_793_884 = this->scale(clamp_750_834, 0, 1, 0, sub_791_882, 1);
        number clamp_797_890 = (Spd_38_37 > 1 ? 1 : (Spd_38_37 < 0 ? 0 : Spd_38_37));
        number clamp_801_895 = (P_24_23 > 60 ? 60 : (P_24_23 < -60 ? -60 : P_24_23));
        number Rst_817_912 = Rst_243_242;
        auto sample_dim_818_913 = this->dim(this->gen_01_sample);
        auto sample_chans_819_914 = this->channels(this->gen_01_sample);
        number gen_820_915 = 0;
        number clamp_822_917 = (int_15_14 > 29 ? 29 : (int_15_14 < 0 ? 0 : int_15_14));
        auto int_823_918 = this->intnum(30);
        number clamp_824_919 = (St_130_129 > 1 ? 1 : (St_130_129 < 0 ? 0 : St_130_129));
        auto int_827_924 = this->intnum(1);
        number clamp_828_925 = (GS_72_71 > 500 ? 500 : (GS_72_71 < 10 ? 10 : GS_72_71));
        auto mstosamps_829_926 = this->mstosamps(clamp_828_925);
        auto int_830_927 = this->intnum(2);
        auto int_831_928 = this->intnum(2);
        number clamp_832_929 = (Pos_183_182 > 1 ? 1 : (Pos_183_182 < 0 ? 0 : Pos_183_182));
        number clamp_833_930 = (D_51_50 > 60 ? 60 : (D_51_50 < 0 ? 0 : D_51_50));
        number clamp_866_969 = (Spy_16_15 > 1 ? 1 : (Spy_16_15 < 0 ? 0 : Spy_16_15));
        auto dim_869_973 = this->dim(this->gen_01_sample);
        number div_870_974 = dim_869_973 / (number)2;
        number div_871_975 = clamp_828_925 / (number)2;
        auto mstosamps_872_976 = this->mstosamps(div_871_975);
        number sub_873_977 = div_870_974 - mstosamps_872_976;
        auto scale_875_979 = this->scale(clamp_832_929, 0, 1, 0, sub_873_977, 1);
        number clamp_879_985 = (Spd_39_38 > 1 ? 1 : (Spd_39_38 < 0 ? 0 : Spd_39_38));
        number clamp_883_990 = (P_25_24 > 60 ? 60 : (P_25_24 < -60 ? -60 : P_25_24));
        number Rst_899_1007 = Rst_243_242;
        number gen_900_1008 = 0;
        auto sample_dim_901_1009 = this->dim(this->gen_01_sample);
        auto sample_chans_902_1010 = this->channels(this->gen_01_sample);
        number clamp_904_1012 = (int_17_16 > 29 ? 29 : (int_17_16 < 0 ? 0 : int_17_16));
        auto int_905_1013 = this->intnum(30);
        number clamp_906_1014 = (St_131_130 > 1 ? 1 : (St_131_130 < 0 ? 0 : St_131_130));
        auto int_909_1019 = this->intnum(1);
        number clamp_910_1020 = (GS_73_72 > 500 ? 500 : (GS_73_72 < 10 ? 10 : GS_73_72));
        auto mstosamps_911_1021 = this->mstosamps(clamp_910_1020);
        number clamp_912_1022 = (D_52_51 > 60 ? 60 : (D_52_51 < 0 ? 0 : D_52_51));
        auto int_942_1056 = this->intnum(2);
        auto int_943_1057 = this->intnum(2);
        number clamp_944_1058 = (Pos_184_183 > 1 ? 1 : (Pos_184_183 < 0 ? 0 : Pos_184_183));
        number clamp_948_1064 = (Spy_26_25 > 1 ? 1 : (Spy_26_25 < 0 ? 0 : Spy_26_25));
        auto dim_951_1068 = this->dim(this->gen_01_sample);
        number div_952_1069 = dim_951_1068 / (number)2;
        number div_953_1070 = clamp_910_1020 / (number)2;
        auto mstosamps_954_1071 = this->mstosamps(div_953_1070);
        number sub_955_1072 = div_952_1069 - mstosamps_954_1071;
        auto scale_957_1074 = this->scale(clamp_944_1058, 0, 1, 0, sub_955_1072, 1);
        number clamp_961_1080 = (Spd_40_39 > 1 ? 1 : (Spd_40_39 < 0 ? 0 : Spd_40_39));
        number clamp_965_1085 = (P_18_17 > 60 ? 60 : (P_18_17 < -60 ? -60 : P_18_17));
        number Rst_981_1102 = Rst_243_242;
        auto sample_dim_982_1103 = this->dim(this->gen_01_sample);
        auto sample_chans_983_1104 = this->channels(this->gen_01_sample);
        number gen_984_1105 = 0;
        number clamp_986_1107 = (int_27_26 > 29 ? 29 : (int_27_26 < 0 ? 0 : int_27_26));
        auto int_987_1108 = this->intnum(30);
        number clamp_988_1109 = (St_132_131 > 1 ? 1 : (St_132_131 < 0 ? 0 : St_132_131));
        auto int_991_1114 = this->intnum(1);
        number clamp_992_1115 = (GS_74_73 > 500 ? 500 : (GS_74_73 < 10 ? 10 : GS_74_73));
        auto mstosamps_993_1116 = this->mstosamps(clamp_992_1115);
        auto int_994_1117 = this->intnum(2);
        auto int_995_1118 = this->intnum(2);
        number clamp_996_1119 = (Pos_185_184 > 1 ? 1 : (Pos_185_184 < 0 ? 0 : Pos_185_184));
        number clamp_997_1120 = (D_53_52 > 60 ? 60 : (D_53_52 < 0 ? 0 : D_53_52));
        number clamp_1030_1160 = (Spy_29_28 > 1 ? 1 : (Spy_29_28 < 0 ? 0 : Spy_29_28));
        auto dim_1033_1164 = this->dim(this->gen_01_sample);
        number div_1034_1165 = dim_1033_1164 / (number)2;
        number div_1035_1166 = clamp_992_1115 / (number)2;
        auto mstosamps_1036_1167 = this->mstosamps(div_1035_1166);
        number sub_1037_1168 = div_1034_1165 - mstosamps_1036_1167;
        auto scale_1039_1170 = this->scale(clamp_996_1119, 0, 1, 0, sub_1037_1168, 1);
        number clamp_1043_1176 = (Spd_41_40 > 1 ? 1 : (Spd_41_40 < 0 ? 0 : Spd_41_40));
        number clamp_1047_1181 = (P_28_27 > 60 ? 60 : (P_28_27 < -60 ? -60 : P_28_27));
        number Rst_1063_1198 = Rst_243_242;
        number gen_1064_1199 = 0;
        auto sample_dim_1065_1200 = this->dim(this->gen_01_sample);
        auto sample_chans_1066_1201 = this->channels(this->gen_01_sample);
        number clamp_1068_1203 = (int_30_29 > 29 ? 29 : (int_30_29 < 0 ? 0 : int_30_29));
        auto int_1069_1204 = this->intnum(30);
        number clamp_1070_1205 = (St_133_132 > 1 ? 1 : (St_133_132 < 0 ? 0 : St_133_132));
        auto int_1073_1210 = this->intnum(1);
        number clamp_1074_1211 = (GS_75_74 > 500 ? 500 : (GS_75_74 < 10 ? 10 : GS_75_74));
        auto mstosamps_1075_1212 = this->mstosamps(clamp_1074_1211);
        auto int_1076_1213 = this->intnum(2);
        auto int_1077_1214 = this->intnum(2);
        number clamp_1078_1215 = (Pos_186_185 > 1 ? 1 : (Pos_186_185 < 0 ? 0 : Pos_186_185));
        number clamp_1079_1216 = (D_54_53 > 60 ? 60 : (D_54_53 < 0 ? 0 : D_54_53));
        number clamp_1112_1255 = (Spy_42_41 > 1 ? 1 : (Spy_42_41 < 0 ? 0 : Spy_42_41));
        auto dim_1115_1259 = this->dim(this->gen_01_sample);
        number div_1116_1260 = dim_1115_1259 / (number)2;
        number div_1117_1261 = clamp_1074_1211 / (number)2;
        auto mstosamps_1118_1262 = this->mstosamps(div_1117_1261);
        number sub_1119_1263 = div_1116_1260 - mstosamps_1118_1262;
        auto scale_1121_1265 = this->scale(clamp_1078_1215, 0, 1, 0, sub_1119_1263, 1);
        number clamp_1125_1271 = (Spd_32_31 > 1 ? 1 : (Spd_32_31 < 0 ? 0 : Spd_32_31));
        number clamp_1129_1276 = (P_31_30 > 60 ? 60 : (P_31_30 < -60 ? -60 : P_31_30));
        number Rst_1145_1294 = Rst_243_242;
        number gen_1146_1295 = 0;
        auto sample_dim_1147_1296 = this->dim(this->gen_01_sample);
        auto sample_chans_1148_1297 = this->channels(this->gen_01_sample);
        number clamp_1150_1299 = (int_43_42 > 29 ? 29 : (int_43_42 < 0 ? 0 : int_43_42));
        auto int_1151_1300 = this->intnum(30);
        number clamp_1152_1301 = (St_134_133 > 1 ? 1 : (St_134_133 < 0 ? 0 : St_134_133));
        auto int_1155_1306 = this->intnum(1);
        number clamp_1156_1307 = (GS_76_75 > 500 ? 500 : (GS_76_75 < 10 ? 10 : GS_76_75));
        auto mstosamps_1157_1308 = this->mstosamps(clamp_1156_1307);
        auto int_1158_1309 = this->intnum(2);
        auto int_1159_1310 = this->intnum(2);
        number clamp_1160_1311 = (Pos_187_186 > 1 ? 1 : (Pos_187_186 < 0 ? 0 : Pos_187_186));
        number clamp_1161_1312 = (D_44_43 > 60 ? 60 : (D_44_43 < 0 ? 0 : D_44_43));
        number clamp_1194_1351 = (Spy_57_56 > 1 ? 1 : (Spy_57_56 < 0 ? 0 : Spy_57_56));
        auto dim_1197_1355 = this->dim(this->gen_01_sample);
        number div_1198_1356 = dim_1197_1355 / (number)2;
        number div_1199_1357 = clamp_1156_1307 / (number)2;
        auto mstosamps_1200_1358 = this->mstosamps(div_1199_1357);
        number sub_1201_1359 = div_1198_1356 - mstosamps_1200_1358;
        auto scale_1203_1361 = this->scale(clamp_1160_1311, 0, 1, 0, sub_1201_1359, 1);
        number clamp_1207_1367 = (Spd_56_55 > 1 ? 1 : (Spd_56_55 < 0 ? 0 : Spd_56_55));
        number clamp_1211_1373 = (P_55_54 > 60 ? 60 : (P_55_54 < -60 ? -60 : P_55_54));
        number Rst_1227_1390 = Rst_243_242;
        number gen_1228_1391 = 0;
        auto sample_dim_1229_1392 = this->dim(this->gen_01_sample);
        auto sample_chans_1230_1393 = this->channels(this->gen_01_sample);
        number clamp_1232_1395 = (int_58_57 > 29 ? 29 : (int_58_57 < 0 ? 0 : int_58_57));
        auto int_1233_1396 = this->intnum(30);
        number clamp_1234_1397 = (St_135_134 > 1 ? 1 : (St_135_134 < 0 ? 0 : St_135_134));
        auto int_1237_1403 = this->intnum(1);
        number clamp_1238_1404 = (GS_77_76 > 500 ? 500 : (GS_77_76 < 10 ? 10 : GS_77_76));
        auto mstosamps_1239_1405 = this->mstosamps(clamp_1238_1404);
        auto int_1240_1406 = this->intnum(2);
        auto int_1241_1407 = this->intnum(2);
        number clamp_1242_1408 = (Pos_188_187 > 1 ? 1 : (Pos_188_187 < 0 ? 0 : Pos_188_187));
        number clamp_1243_1409 = (D_59_58 > 60 ? 60 : (D_59_58 < 0 ? 0 : D_59_58));
        number clamp_1276_1448 = (Spy_62_61 > 1 ? 1 : (Spy_62_61 < 0 ? 0 : Spy_62_61));
        auto dim_1279_1452 = this->dim(this->gen_01_sample);
        number div_1280_1453 = dim_1279_1452 / (number)2;
        number div_1281_1454 = clamp_1238_1404 / (number)2;
        auto mstosamps_1282_1455 = this->mstosamps(div_1281_1454);
        number sub_1283_1456 = div_1280_1453 - mstosamps_1282_1455;
        auto scale_1285_1458 = this->scale(clamp_1242_1408, 0, 1, 0, sub_1283_1456, 1);
        number clamp_1289_1464 = (Spd_61_60 > 1 ? 1 : (Spd_61_60 < 0 ? 0 : Spd_61_60));
        number clamp_1293_1469 = (P_60_59 > 60 ? 60 : (P_60_59 < -60 ? -60 : P_60_59));
        number Rst_1309_1486 = Rst_243_242;
        number gen_1310_1487 = 0;
        auto sample_dim_1311_1488 = this->dim(this->gen_01_sample);
        auto sample_chans_1312_1489 = this->channels(this->gen_01_sample);
        number clamp_1314_1491 = (int_63_62 > 29 ? 29 : (int_63_62 < 0 ? 0 : int_63_62));
        auto int_1315_1492 = this->intnum(30);
        number clamp_1316_1493 = (St_136_135 > 1 ? 1 : (St_136_135 < 0 ? 0 : St_136_135));
        auto int_1319_1498 = this->intnum(1);
        number clamp_1320_1499 = (GS_65_64 > 500 ? 500 : (GS_65_64 < 10 ? 10 : GS_65_64));
        auto mstosamps_1321_1500 = this->mstosamps(clamp_1320_1499);
        auto int_1322_1501 = this->intnum(2);
        auto int_1323_1502 = this->intnum(2);
        number clamp_1324_1503 = (Pos_189_188 > 1 ? 1 : (Pos_189_188 < 0 ? 0 : Pos_189_188));
        number clamp_1325_1504 = (D_64_63 > 60 ? 60 : (D_64_63 < 0 ? 0 : D_64_63));
        number clamp_1358_1543 = (Spy_80_79 > 1 ? 1 : (Spy_80_79 < 0 ? 0 : Spy_80_79));
        auto dim_1361_1547 = this->dim(this->gen_01_sample);
        number div_1362_1548 = dim_1361_1547 / (number)2;
        number div_1363_1549 = clamp_1320_1499 / (number)2;
        auto mstosamps_1364_1550 = this->mstosamps(div_1363_1549);
        number sub_1365_1551 = div_1362_1548 - mstosamps_1364_1550;
        auto scale_1367_1553 = this->scale(clamp_1324_1503, 0, 1, 0, sub_1365_1551, 1);
        number clamp_1371_1559 = (Spd_79_78 > 1 ? 1 : (Spd_79_78 < 0 ? 0 : Spd_79_78));
        number clamp_1375_1564 = (P_78_77 > 60 ? 60 : (P_78_77 < -60 ? -60 : P_78_77));
        number Rst_1391_1581 = Rst_243_242;
        auto sample_dim_1392_1582 = this->dim(this->gen_01_sample);
        auto sample_chans_1393_1583 = this->channels(this->gen_01_sample);
        number gen_1394_1584 = 0;
        number clamp_1396_1586 = (int_87_86 > 29 ? 29 : (int_87_86 < 0 ? 0 : int_87_86));
        auto int_1397_1587 = this->intnum(30);
        number clamp_1398_1588 = (St_138_137 > 1 ? 1 : (St_138_137 < 0 ? 0 : St_138_137));
        auto int_1401_1593 = this->intnum(1);
        number clamp_1402_1594 = (GS_89_88 > 500 ? 500 : (GS_89_88 < 10 ? 10 : GS_89_88));
        auto mstosamps_1403_1595 = this->mstosamps(clamp_1402_1594);
        number clamp_1404_1596 = (D_88_87 > 60 ? 60 : (D_88_87 < 0 ? 0 : D_88_87));
        auto int_1434_1630 = this->intnum(2);
        auto int_1435_1631 = this->intnum(2);
        number clamp_1436_1632 = (Pos_191_190 > 1 ? 1 : (Pos_191_190 < 0 ? 0 : Pos_191_190));
        number clamp_1440_1638 = (Spy_92_91 > 1 ? 1 : (Spy_92_91 < 0 ? 0 : Spy_92_91));
        auto dim_1443_1642 = this->dim(this->gen_01_sample);
        number div_1444_1643 = dim_1443_1642 / (number)2;
        number div_1445_1644 = clamp_1402_1594 / (number)2;
        auto mstosamps_1446_1645 = this->mstosamps(div_1445_1644);
        number sub_1447_1646 = div_1444_1643 - mstosamps_1446_1645;
        auto scale_1449_1648 = this->scale(clamp_1436_1632, 0, 1, 0, sub_1447_1646, 1);
        number clamp_1453_1654 = (Spd_91_90 > 1 ? 1 : (Spd_91_90 < 0 ? 0 : Spd_91_90));
        number clamp_1457_1659 = (P_90_89 > 60 ? 60 : (P_90_89 < -60 ? -60 : P_90_89));
        number Rst_1473_1677 = Rst_243_242;
        auto sample_dim_1474_1678 = this->dim(this->gen_01_sample);
        auto sample_chans_1475_1679 = this->channels(this->gen_01_sample);
        number gen_1476_1680 = 0;
        number clamp_1478_1682 = (int_93_92 > 29 ? 29 : (int_93_92 < 0 ? 0 : int_93_92));
        auto int_1479_1683 = this->intnum(30);
        number clamp_1480_1684 = (St_139_138 > 1 ? 1 : (St_139_138 < 0 ? 0 : St_139_138));
        auto int_1483_1689 = this->intnum(1);
        number clamp_1484_1690 = (GS_95_94 > 500 ? 500 : (GS_95_94 < 10 ? 10 : GS_95_94));
        auto mstosamps_1485_1691 = this->mstosamps(clamp_1484_1690);
        number clamp_1486_1692 = (D_94_93 > 60 ? 60 : (D_94_93 < 0 ? 0 : D_94_93));
        auto int_1516_1727 = this->intnum(2);
        auto int_1517_1728 = this->intnum(2);
        number clamp_1518_1729 = (Pos_192_191 > 1 ? 1 : (Pos_192_191 < 0 ? 0 : Pos_192_191));
        number clamp_1522_1735 = (Spy_98_97 > 1 ? 1 : (Spy_98_97 < 0 ? 0 : Spy_98_97));
        auto dim_1525_1739 = this->dim(this->gen_01_sample);
        number div_1526_1740 = dim_1525_1739 / (number)2;
        number div_1527_1741 = clamp_1484_1690 / (number)2;
        auto mstosamps_1528_1742 = this->mstosamps(div_1527_1741);
        number sub_1529_1743 = div_1526_1740 - mstosamps_1528_1742;
        auto scale_1531_1745 = this->scale(clamp_1518_1729, 0, 1, 0, sub_1529_1743, 1);
        number clamp_1535_1751 = (Spd_97_96 > 1 ? 1 : (Spd_97_96 < 0 ? 0 : Spd_97_96));
        number clamp_1539_1756 = (P_96_95 > 60 ? 60 : (P_96_95 < -60 ? -60 : P_96_95));
        number Rst_1555_1773 = Rst_243_242;
        auto sample_dim_1556_1774 = this->dim(this->gen_01_sample);
        auto sample_chans_1557_1775 = this->channels(this->gen_01_sample);
        number gen_1558_1776 = 0;
        number clamp_1560_1778 = (int_99_98 > 29 ? 29 : (int_99_98 < 0 ? 0 : int_99_98));
        auto int_1561_1779 = this->intnum(30);
        number clamp_1562_1780 = (St_140_139 > 1 ? 1 : (St_140_139 < 0 ? 0 : St_140_139));
        auto int_1565_1785 = this->intnum(1);
        number clamp_1566_1786 = (GS_101_100 > 500 ? 500 : (GS_101_100 < 10 ? 10 : GS_101_100));
        auto mstosamps_1567_1787 = this->mstosamps(clamp_1566_1786);
        auto int_1568_1788 = this->intnum(2);
        auto int_1569_1789 = this->intnum(2);
        number clamp_1570_1790 = (Pos_193_192 > 1 ? 1 : (Pos_193_192 < 0 ? 0 : Pos_193_192));
        number clamp_1571_1791 = (D_100_99 > 60 ? 60 : (D_100_99 < 0 ? 0 : D_100_99));
        number clamp_1604_1830 = (Spy_104_103 > 1 ? 1 : (Spy_104_103 < 0 ? 0 : Spy_104_103));
        auto dim_1607_1834 = this->dim(this->gen_01_sample);
        number div_1608_1835 = dim_1607_1834 / (number)2;
        number div_1609_1836 = clamp_1566_1786 / (number)2;
        auto mstosamps_1610_1837 = this->mstosamps(div_1609_1836);
        number sub_1611_1838 = div_1608_1835 - mstosamps_1610_1837;
        auto scale_1613_1840 = this->scale(clamp_1570_1790, 0, 1, 0, sub_1611_1838, 1);
        number clamp_1617_1846 = (Spd_103_102 > 1 ? 1 : (Spd_103_102 < 0 ? 0 : Spd_103_102));
        number clamp_1621_1851 = (P_102_101 > 60 ? 60 : (P_102_101 < -60 ? -60 : P_102_101));
        number Rst_1637_1868 = Rst_243_242;
        auto sample_dim_1638_1869 = this->dim(this->gen_01_sample);
        auto sample_chans_1639_1870 = this->channels(this->gen_01_sample);
        number gen_1640_1871 = 0;
        number clamp_1642_1873 = (int_105_104 > 29 ? 29 : (int_105_104 < 0 ? 0 : int_105_104));
        auto int_1643_1874 = this->intnum(30);
        number clamp_1644_1875 = (St_141_140 > 1 ? 1 : (St_141_140 < 0 ? 0 : St_141_140));
        auto int_1647_1880 = this->intnum(1);
        number clamp_1648_1881 = (GS_107_106 > 500 ? 500 : (GS_107_106 < 10 ? 10 : GS_107_106));
        auto mstosamps_1649_1882 = this->mstosamps(clamp_1648_1881);
        auto int_1650_1883 = this->intnum(2);
        auto int_1651_1884 = this->intnum(2);
        number clamp_1652_1885 = (Pos_194_193 > 1 ? 1 : (Pos_194_193 < 0 ? 0 : Pos_194_193));
        number clamp_1653_1886 = (D_106_105 > 60 ? 60 : (D_106_105 < 0 ? 0 : D_106_105));
        number clamp_1686_1925 = (Spy_110_109 > 1 ? 1 : (Spy_110_109 < 0 ? 0 : Spy_110_109));
        auto dim_1689_1929 = this->dim(this->gen_01_sample);
        number div_1690_1930 = dim_1689_1929 / (number)2;
        number div_1691_1931 = clamp_1648_1881 / (number)2;
        auto mstosamps_1692_1932 = this->mstosamps(div_1691_1931);
        number sub_1693_1933 = div_1690_1930 - mstosamps_1692_1932;
        auto scale_1695_1935 = this->scale(clamp_1652_1885, 0, 1, 0, sub_1693_1933, 1);
        number clamp_1699_1941 = (Spd_109_108 > 1 ? 1 : (Spd_109_108 < 0 ? 0 : Spd_109_108));
        number clamp_1703_1947 = (P_108_107 > 60 ? 60 : (P_108_107 < -60 ? -60 : P_108_107));
        number Rst_1719_1964 = Rst_243_242;
        number gen_1720_1965 = 0;
        auto sample_dim_1721_1966 = this->dim(this->gen_01_sample);
        auto sample_chans_1722_1967 = this->channels(this->gen_01_sample);
        number clamp_1724_1969 = (int_111_110 > 29 ? 29 : (int_111_110 < 0 ? 0 : int_111_110));
        auto int_1725_1970 = this->intnum(30);
        number clamp_1726_1971 = (St_142_141 > 1 ? 1 : (St_142_141 < 0 ? 0 : St_142_141));
        auto int_1729_1977 = this->intnum(1);
        number clamp_1730_1978 = (GS_113_112 > 500 ? 500 : (GS_113_112 < 10 ? 10 : GS_113_112));
        auto mstosamps_1731_1979 = this->mstosamps(clamp_1730_1978);
        number clamp_1732_1980 = (D_112_111 > 60 ? 60 : (D_112_111 < 0 ? 0 : D_112_111));
        auto int_1762_2015 = this->intnum(2);
        auto int_1763_2016 = this->intnum(2);
        number clamp_1764_2017 = (Pos_195_194 > 1 ? 1 : (Pos_195_194 < 0 ? 0 : Pos_195_194));
        number clamp_1768_2023 = (Spy_116_115 > 1 ? 1 : (Spy_116_115 < 0 ? 0 : Spy_116_115));
        auto dim_1771_2028 = this->dim(this->gen_01_sample);
        number div_1772_2029 = dim_1771_2028 / (number)2;
        number div_1773_2030 = clamp_1730_1978 / (number)2;
        auto mstosamps_1774_2031 = this->mstosamps(div_1773_2030);
        number sub_1775_2032 = div_1772_2029 - mstosamps_1774_2031;
        auto scale_1777_2034 = this->scale(clamp_1764_2017, 0, 1, 0, sub_1775_2032, 1);
        number clamp_1781_2040 = (Spd_115_114 > 1 ? 1 : (Spd_115_114 < 0 ? 0 : Spd_115_114));
        number clamp_1785_2045 = (P_114_113 > 60 ? 60 : (P_114_113 < -60 ? -60 : P_114_113));
        number Rst_1801_2062 = Rst_243_242;
        number gen_1802_2063 = 0;
        auto sample_dim_1803_2064 = this->dim(this->gen_01_sample);
        auto sample_chans_1804_2065 = this->channels(this->gen_01_sample);
        number clamp_1806_2067 = (int_117_116 > 29 ? 29 : (int_117_116 < 0 ? 0 : int_117_116));
        auto int_1807_2068 = this->intnum(30);
        number clamp_1808_2069 = (St_123_122 > 1 ? 1 : (St_123_122 < 0 ? 0 : St_123_122));
        auto int_1811_2074 = this->intnum(1);
        number clamp_1812_2075 = (GS_119_118 > 500 ? 500 : (GS_119_118 < 10 ? 10 : GS_119_118));
        auto mstosamps_1813_2076 = this->mstosamps(clamp_1812_2075);
        number clamp_1814_2077 = (D_118_117 > 60 ? 60 : (D_118_117 < 0 ? 0 : D_118_117));
        auto int_1844_2112 = this->intnum(2);
        auto int_1845_2113 = this->intnum(2);
        number clamp_1846_2114 = (Pos_196_195 > 1 ? 1 : (Pos_196_195 < 0 ? 0 : Pos_196_195));
        number clamp_1850_2120 = (Spy_122_121 > 1 ? 1 : (Spy_122_121 < 0 ? 0 : Spy_122_121));
        auto dim_1853_2124 = this->dim(this->gen_01_sample);
        number div_1854_2125 = dim_1853_2124 / (number)2;
        number div_1855_2126 = clamp_1812_2075 / (number)2;
        auto mstosamps_1856_2127 = this->mstosamps(div_1855_2126);
        number sub_1857_2128 = div_1854_2125 - mstosamps_1856_2127;
        auto scale_1859_2130 = this->scale(clamp_1846_2114, 0, 1, 0, sub_1857_2128, 1);
        number clamp_1863_2136 = (Spd_121_120 > 1 ? 1 : (Spd_121_120 < 0 ? 0 : Spd_121_120));
        number clamp_1867_2142 = (P_120_119 > 60 ? 60 : (P_120_119 < -60 ? -60 : P_120_119));
        number Rst_1883_2159 = Rst_243_242;
        number gen_1884_2160 = 0;
        auto sample_dim_1885_2161 = this->dim(this->gen_01_sample);
        auto sample_chans_1886_2162 = this->channels(this->gen_01_sample);
        number clamp_1888_2164 = (int_143_142 > 29 ? 29 : (int_143_142 < 0 ? 0 : int_143_142));
        auto int_1889_2165 = this->intnum(30);
        number clamp_1890_2166 = (St_149_148 > 1 ? 1 : (St_149_148 < 0 ? 0 : St_149_148));
        auto int_1893_2171 = this->intnum(1);
        number clamp_1894_2172 = (GS_145_144 > 500 ? 500 : (GS_145_144 < 10 ? 10 : GS_145_144));
        auto mstosamps_1895_2173 = this->mstosamps(clamp_1894_2172);
        auto int_1896_2174 = this->intnum(2);
        auto int_1897_2175 = this->intnum(2);
        number clamp_1898_2176 = (Pos_197_196 > 1 ? 1 : (Pos_197_196 < 0 ? 0 : Pos_197_196));
        number clamp_1899_2177 = (D_144_143 > 60 ? 60 : (D_144_143 < 0 ? 0 : D_144_143));
        number clamp_1932_2216 = (Spy_148_147 > 1 ? 1 : (Spy_148_147 < 0 ? 0 : Spy_148_147));
        auto dim_1935_2220 = this->dim(this->gen_01_sample);
        number div_1936_2221 = dim_1935_2220 / (number)2;
        number div_1937_2222 = clamp_1894_2172 / (number)2;
        auto mstosamps_1938_2223 = this->mstosamps(div_1937_2222);
        number sub_1939_2224 = div_1936_2221 - mstosamps_1938_2223;
        auto scale_1941_2226 = this->scale(clamp_1898_2176, 0, 1, 0, sub_1939_2224, 1);
        number clamp_1945_2232 = (Spd_147_146 > 1 ? 1 : (Spd_147_146 < 0 ? 0 : Spd_147_146));
        number clamp_1949_2237 = (P_146_145 > 60 ? 60 : (P_146_145 < -60 ? -60 : P_146_145));
        number Rst_1965_2254 = Rst_243_242;
        auto sample_dim_1966_2255 = this->dim(this->gen_01_sample);
        auto sample_chans_1967_2256 = this->channels(this->gen_01_sample);
        number gen_1968_2257 = 0;
        number clamp_1970_2259 = (int_150_149 > 29 ? 29 : (int_150_149 < 0 ? 0 : int_150_149));
        auto int_1971_2260 = this->intnum(30);
        number clamp_1972_2261 = (St_156_155 > 1 ? 1 : (St_156_155 < 0 ? 0 : St_156_155));
        auto int_1975_2266 = this->intnum(1);
        number clamp_1976_2267 = (GS_152_151 > 500 ? 500 : (GS_152_151 < 10 ? 10 : GS_152_151));
        auto mstosamps_1977_2268 = this->mstosamps(clamp_1976_2267);
        auto int_1978_2269 = this->intnum(2);
        auto int_1979_2270 = this->intnum(2);
        number clamp_1980_2271 = (Pos_198_197 > 1 ? 1 : (Pos_198_197 < 0 ? 0 : Pos_198_197));
        number clamp_1981_2272 = (D_151_150 > 60 ? 60 : (D_151_150 < 0 ? 0 : D_151_150));
        number clamp_2014_2311 = (Spy_155_154 > 1 ? 1 : (Spy_155_154 < 0 ? 0 : Spy_155_154));
        auto dim_2017_2315 = this->dim(this->gen_01_sample);
        number div_2018_2316 = dim_2017_2315 / (number)2;
        number div_2019_2317 = clamp_1976_2267 / (number)2;
        auto mstosamps_2020_2318 = this->mstosamps(div_2019_2317);
        number sub_2021_2319 = div_2018_2316 - mstosamps_2020_2318;
        auto scale_2023_2321 = this->scale(clamp_1980_2271, 0, 1, 0, sub_2021_2319, 1);
        number clamp_2027_2327 = (Spd_154_153 > 1 ? 1 : (Spd_154_153 < 0 ? 0 : Spd_154_153));
        number clamp_2031_2332 = (P_153_152 > 60 ? 60 : (P_153_152 < -60 ? -60 : P_153_152));
        number Rst_2047_2349 = Rst_243_242;
        number gen_2048_2350 = 0;
        auto sample_dim_2049_2351 = this->dim(this->gen_01_sample);
        auto sample_chans_2050_2352 = this->channels(this->gen_01_sample);
        number clamp_2052_2354 = (int_157_156 > 29 ? 29 : (int_157_156 < 0 ? 0 : int_157_156));
        auto int_2053_2355 = this->intnum(30);
        number clamp_2054_2356 = (St_163_162 > 1 ? 1 : (St_163_162 < 0 ? 0 : St_163_162));
        auto int_2057_2361 = this->intnum(1);
        number clamp_2058_2362 = (GS_159_158 > 500 ? 500 : (GS_159_158 < 10 ? 10 : GS_159_158));
        auto mstosamps_2059_2363 = this->mstosamps(clamp_2058_2362);
        auto int_2060_2364 = this->intnum(2);
        auto int_2061_2365 = this->intnum(2);
        number clamp_2062_2366 = (Pos_199_198 > 1 ? 1 : (Pos_199_198 < 0 ? 0 : Pos_199_198));
        number clamp_2063_2367 = (D_158_157 > 60 ? 60 : (D_158_157 < 0 ? 0 : D_158_157));
        number clamp_2096_2406 = (Spy_162_161 > 1 ? 1 : (Spy_162_161 < 0 ? 0 : Spy_162_161));
        auto dim_2099_2410 = this->dim(this->gen_01_sample);
        number div_2100_2411 = dim_2099_2410 / (number)2;
        number div_2101_2412 = clamp_2058_2362 / (number)2;
        auto mstosamps_2102_2413 = this->mstosamps(div_2101_2412);
        number sub_2103_2414 = div_2100_2411 - mstosamps_2102_2413;
        auto scale_2105_2416 = this->scale(clamp_2062_2366, 0, 1, 0, sub_2103_2414, 1);
        number clamp_2109_2422 = (Spd_161_160 > 1 ? 1 : (Spd_161_160 < 0 ? 0 : Spd_161_160));
        number clamp_2113_2427 = (P_160_159 > 60 ? 60 : (P_160_159 < -60 ? -60 : P_160_159));
        number Rst_2129_2444 = Rst_243_242;
        auto sample_dim_2130_2445 = this->dim(this->gen_01_sample);
        auto sample_chans_2131_2446 = this->channels(this->gen_01_sample);
        number gen_2132_2447 = 0;
        number clamp_2134_2449 = (int_164_163 > 29 ? 29 : (int_164_163 < 0 ? 0 : int_164_163));
        auto int_2135_2450 = this->intnum(30);
        number clamp_2136_2451 = (St_170_169 > 1 ? 1 : (St_170_169 < 0 ? 0 : St_170_169));
        auto int_2139_2456 = this->intnum(1);
        number clamp_2140_2457 = (GS_166_165 > 500 ? 500 : (GS_166_165 < 10 ? 10 : GS_166_165));
        auto mstosamps_2141_2458 = this->mstosamps(clamp_2140_2457);
        auto int_2142_2459 = this->intnum(2);
        auto int_2143_2460 = this->intnum(2);
        number clamp_2144_2461 = (Pos_200_199 > 1 ? 1 : (Pos_200_199 < 0 ? 0 : Pos_200_199));
        number clamp_2145_2462 = (D_165_164 > 60 ? 60 : (D_165_164 < 0 ? 0 : D_165_164));
        number clamp_2178_2502 = (Spy_169_168 > 1 ? 1 : (Spy_169_168 < 0 ? 0 : Spy_169_168));
        auto dim_2181_2506 = this->dim(this->gen_01_sample);
        number div_2182_2507 = dim_2181_2506 / (number)2;
        number div_2183_2508 = clamp_2140_2457 / (number)2;
        auto mstosamps_2184_2509 = this->mstosamps(div_2183_2508);
        number sub_2185_2510 = div_2182_2507 - mstosamps_2184_2509;
        auto scale_2187_2512 = this->scale(clamp_2144_2461, 0, 1, 0, sub_2185_2510, 1);
        number clamp_2191_2518 = (Spd_168_167 > 1 ? 1 : (Spd_168_167 < 0 ? 0 : Spd_168_167));
        number clamp_2195_2523 = (P_167_166 > 60 ? 60 : (P_167_166 < -60 ? -60 : P_167_166));
        number Rst_2211_2541 = Rst_243_242;
        auto sample_dim_2212_2542 = this->dim(this->gen_01_sample);
        auto sample_chans_2213_2543 = this->channels(this->gen_01_sample);
        number gen_2214_2544 = 0;
        number clamp_2216_2546 = (int_171_170 > 29 ? 29 : (int_171_170 < 0 ? 0 : int_171_170));
        auto int_2217_2547 = this->intnum(30);
        number clamp_2218_2548 = (St_202_201 > 1 ? 1 : (St_202_201 < 0 ? 0 : St_202_201));
        auto int_2221_2553 = this->intnum(1);
        number clamp_2222_2554 = (GS_173_172 > 500 ? 500 : (GS_173_172 < 10 ? 10 : GS_173_172));
        auto mstosamps_2223_2555 = this->mstosamps(clamp_2222_2554);
        auto int_2224_2556 = this->intnum(2);
        auto int_2225_2557 = this->intnum(2);
        number clamp_2226_2558 = (Pos_176_175 > 1 ? 1 : (Pos_176_175 < 0 ? 0 : Pos_176_175));
        number clamp_2227_2559 = (D_172_171 > 60 ? 60 : (D_172_171 < 0 ? 0 : D_172_171));
        number clamp_2260_2598 = (Spy_201_200 > 1 ? 1 : (Spy_201_200 < 0 ? 0 : Spy_201_200));
        auto dim_2263_2602 = this->dim(this->gen_01_sample);
        number div_2264_2603 = dim_2263_2602 / (number)2;
        number div_2265_2604 = clamp_2222_2554 / (number)2;
        auto mstosamps_2266_2605 = this->mstosamps(div_2265_2604);
        number sub_2267_2606 = div_2264_2603 - mstosamps_2266_2605;
        auto scale_2269_2608 = this->scale(clamp_2226_2558, 0, 1, 0, sub_2267_2606, 1);
        number clamp_2273_2614 = (Spd_175_174 > 1 ? 1 : (Spd_175_174 < 0 ? 0 : Spd_175_174));
        number clamp_2277_2619 = (P_174_173 > 60 ? 60 : (P_174_173 < -60 ? -60 : P_174_173));
        number Rst_2293_2636 = Rst_243_242;
        auto sample_dim_2294_2637 = this->dim(this->gen_01_sample);
        auto sample_chans_2295_2638 = this->channels(this->gen_01_sample);
        number gen_2296_2639 = 0;
        number clamp_2298_2641 = (int_203_202 > 29 ? 29 : (int_203_202 < 0 ? 0 : int_203_202));
        auto int_2299_2642 = this->intnum(30);
        number clamp_2300_2643 = (St_210_209 > 1 ? 1 : (St_210_209 < 0 ? 0 : St_210_209));
        auto int_2303_2648 = this->intnum(1);
        number clamp_2304_2649 = (GS_205_204 > 500 ? 500 : (GS_205_204 < 10 ? 10 : GS_205_204));
        auto mstosamps_2305_2650 = this->mstosamps(clamp_2304_2649);
        number clamp_2306_2651 = (D_204_203 > 60 ? 60 : (D_204_203 < 0 ? 0 : D_204_203));
        auto int_2336_2686 = this->intnum(2);
        auto int_2337_2687 = this->intnum(2);
        number clamp_2338_2688 = (Pos_208_207 > 1 ? 1 : (Pos_208_207 < 0 ? 0 : Pos_208_207));
        number clamp_2342_2694 = (Spy_209_208 > 1 ? 1 : (Spy_209_208 < 0 ? 0 : Spy_209_208));
        auto dim_2345_2698 = this->dim(this->gen_01_sample);
        number div_2346_2699 = dim_2345_2698 / (number)2;
        number div_2347_2700 = clamp_2304_2649 / (number)2;
        auto mstosamps_2348_2701 = this->mstosamps(div_2347_2700);
        number sub_2349_2702 = div_2346_2699 - mstosamps_2348_2701;
        auto scale_2351_2704 = this->scale(clamp_2338_2688, 0, 1, 0, sub_2349_2702, 1);
        number clamp_2355_2710 = (Spd_207_206 > 1 ? 1 : (Spd_207_206 < 0 ? 0 : Spd_207_206));
        number clamp_2359_2715 = (P_206_205 > 60 ? 60 : (P_206_205 < -60 ? -60 : P_206_205));
        number Rst_2375_2732 = Rst_243_242;
        number gen_2376_2733 = 0;
        auto sample_dim_2377_2734 = this->dim(this->gen_01_sample);
        auto sample_chans_2378_2735 = this->channels(this->gen_01_sample);
        number clamp_2380_2737 = (int_211_210 > 29 ? 29 : (int_211_210 < 0 ? 0 : int_211_210));
        auto int_2381_2738 = this->intnum(30);
        number clamp_2382_2739 = (St_218_217 > 1 ? 1 : (St_218_217 < 0 ? 0 : St_218_217));
        auto int_2385_2744 = this->intnum(1);
        number clamp_2386_2745 = (GS_213_212 > 500 ? 500 : (GS_213_212 < 10 ? 10 : GS_213_212));
        auto mstosamps_2387_2746 = this->mstosamps(clamp_2386_2745);
        auto int_2388_2747 = this->intnum(2);
        auto int_2389_2748 = this->intnum(2);
        number clamp_2390_2749 = (Pos_216_215 > 1 ? 1 : (Pos_216_215 < 0 ? 0 : Pos_216_215));
        number clamp_2391_2750 = (D_212_211 > 60 ? 60 : (D_212_211 < 0 ? 0 : D_212_211));
        number clamp_2424_2789 = (Spy_217_216 > 1 ? 1 : (Spy_217_216 < 0 ? 0 : Spy_217_216));
        auto dim_2427_2793 = this->dim(this->gen_01_sample);
        number div_2428_2794 = dim_2427_2793 / (number)2;
        number div_2429_2795 = clamp_2386_2745 / (number)2;
        auto mstosamps_2430_2796 = this->mstosamps(div_2429_2795);
        number sub_2431_2797 = div_2428_2794 - mstosamps_2430_2796;
        auto scale_2433_2799 = this->scale(clamp_2390_2749, 0, 1, 0, sub_2431_2797, 1);
        number clamp_2437_2805 = (Spd_215_214 > 1 ? 1 : (Spd_215_214 < 0 ? 0 : Spd_215_214));
        number clamp_2441_2810 = (P_214_213 > 60 ? 60 : (P_214_213 < -60 ? -60 : P_214_213));
        number Rst_2457_2827 = Rst_243_242;
        auto sample_dim_2458_2828 = this->dim(this->gen_01_sample);
        auto sample_chans_2459_2829 = this->channels(this->gen_01_sample);
        number gen_2460_2830 = 0;
        number clamp_2462_2832 = (int_219_218 > 29 ? 29 : (int_219_218 < 0 ? 0 : int_219_218));
        auto int_2463_2833 = this->intnum(30);
        number clamp_2464_2834 = (St_226_225 > 1 ? 1 : (St_226_225 < 0 ? 0 : St_226_225));
        auto int_2467_2839 = this->intnum(1);
        number clamp_2468_2840 = (GS_221_220 > 500 ? 500 : (GS_221_220 < 10 ? 10 : GS_221_220));
        auto mstosamps_2469_2841 = this->mstosamps(clamp_2468_2840);
        auto int_2470_2842 = this->intnum(2);
        auto int_2471_2843 = this->intnum(2);
        number clamp_2472_2844 = (Pos_224_223 > 1 ? 1 : (Pos_224_223 < 0 ? 0 : Pos_224_223));
        number clamp_2473_2845 = (D_220_219 > 60 ? 60 : (D_220_219 < 0 ? 0 : D_220_219));
        number clamp_2506_2884 = (Spy_225_224 > 1 ? 1 : (Spy_225_224 < 0 ? 0 : Spy_225_224));
        auto dim_2509_2888 = this->dim(this->gen_01_sample);
        number div_2510_2889 = dim_2509_2888 / (number)2;
        number div_2511_2890 = clamp_2468_2840 / (number)2;
        auto mstosamps_2512_2891 = this->mstosamps(div_2511_2890);
        number sub_2513_2892 = div_2510_2889 - mstosamps_2512_2891;
        auto scale_2515_2894 = this->scale(clamp_2472_2844, 0, 1, 0, sub_2513_2892, 1);
        number clamp_2519_2900 = (Spd_223_222 > 1 ? 1 : (Spd_223_222 < 0 ? 0 : Spd_223_222));
        number clamp_2523_2905 = (P_222_221 > 60 ? 60 : (P_222_221 < -60 ? -60 : P_222_221));
        number Rst_2539_2922 = Rst_243_242;
        number gen_2540_2923 = 0;
        auto sample_dim_2541_2924 = this->dim(this->gen_01_sample);
        auto sample_chans_2542_2925 = this->channels(this->gen_01_sample);
        number clamp_2544_2927 = (int_227_226 > 29 ? 29 : (int_227_226 < 0 ? 0 : int_227_226));
        auto int_2545_2928 = this->intnum(30);
        number clamp_2546_2929 = (St_234_233 > 1 ? 1 : (St_234_233 < 0 ? 0 : St_234_233));
        auto int_2549_2934 = this->intnum(1);
        number clamp_2550_2935 = (GS_229_228 > 500 ? 500 : (GS_229_228 < 10 ? 10 : GS_229_228));
        auto mstosamps_2551_2936 = this->mstosamps(clamp_2550_2935);
        number clamp_2552_2937 = (D_228_227 > 60 ? 60 : (D_228_227 < 0 ? 0 : D_228_227));
        auto int_2582_2971 = this->intnum(2);
        auto int_2583_2972 = this->intnum(2);
        number clamp_2584_2973 = (Pos_232_231 > 1 ? 1 : (Pos_232_231 < 0 ? 0 : Pos_232_231));
        number clamp_2588_2979 = (Spy_233_232 > 1 ? 1 : (Spy_233_232 < 0 ? 0 : Spy_233_232));
        auto dim_2591_2983 = this->dim(this->gen_01_sample);
        number div_2592_2984 = dim_2591_2983 / (number)2;
        number div_2593_2985 = clamp_2550_2935 / (number)2;
        auto mstosamps_2594_2986 = this->mstosamps(div_2593_2985);
        number sub_2595_2987 = div_2592_2984 - mstosamps_2594_2986;
        auto scale_2597_2989 = this->scale(clamp_2584_2973, 0, 1, 0, sub_2595_2987, 1);
        number clamp_2601_2995 = (Spd_231_230 > 1 ? 1 : (Spd_231_230 < 0 ? 0 : Spd_231_230));
        number clamp_2605_3000 = (P_230_229 > 60 ? 60 : (P_230_229 < -60 ? -60 : P_230_229));
        number Rst_2621_3017 = Rst_243_242;
        number gen_2622_3018 = 0;
        auto sample_dim_2623_3019 = this->dim(this->gen_01_sample);
        auto sample_chans_2624_3020 = this->channels(this->gen_01_sample);
        number clamp_2626_3022 = (int_235_234 > 29 ? 29 : (int_235_234 < 0 ? 0 : int_235_234));
        auto int_2627_3023 = this->intnum(30);
        number clamp_2628_3024 = (St_242_241 > 1 ? 1 : (St_242_241 < 0 ? 0 : St_242_241));
        auto int_2631_3029 = this->intnum(1);
        number clamp_2632_3030 = (GS_237_236 > 500 ? 500 : (GS_237_236 < 10 ? 10 : GS_237_236));
        auto mstosamps_2633_3031 = this->mstosamps(clamp_2632_3030);
        auto int_2634_3032 = this->intnum(2);
        auto int_2635_3033 = this->intnum(2);
        number clamp_2636_3034 = (Pos_240_239 > 1 ? 1 : (Pos_240_239 < 0 ? 0 : Pos_240_239));
        number clamp_2637_3035 = (D_236_235 > 60 ? 60 : (D_236_235 < 0 ? 0 : D_236_235));
        number clamp_2670_3074 = (Spy_241_240 > 1 ? 1 : (Spy_241_240 < 0 ? 0 : Spy_241_240));
        auto dim_2673_3078 = this->dim(this->gen_01_sample);
        number div_2674_3079 = dim_2673_3078 / (number)2;
        number div_2675_3080 = clamp_2632_3030 / (number)2;
        auto mstosamps_2676_3081 = this->mstosamps(div_2675_3080);
        number sub_2677_3082 = div_2674_3079 - mstosamps_2676_3081;
        auto scale_2679_3084 = this->scale(clamp_2636_3034, 0, 1, 0, sub_2677_3082, 1);
        number clamp_2683_3090 = (Spd_239_238 > 1 ? 1 : (Spd_239_238 < 0 ? 0 : Spd_239_238));
        number clamp_2687_3095 = (P_238_237 > 60 ? 60 : (P_238_237 < -60 ? -60 : P_238_237));
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number float_247_246 = float(0.5);
            number slide_251_251 = this->gen_01_slide_250_next(clamp_250_249, this->sr / (number)100, this->sr / (number)100);
            number noise_252_254 = this->gen_01_noise_253_next();
            number slide_260_263 = this->gen_01_slide_262_next(clamp_259_261, this->sr / (number)100, this->sr / (number)100);
            number phasor_261_265 = this->gen_01_phasor_264_next(slide_260_263, 0);
            number delta_262_267 = this->gen_01_delta_266_next(phasor_261_265);
            number lt_263_268 = delta_262_267 < 0;
            number counter_264 = 0;
            number counter_265 = 0;
            number counter_266 = 0;
            array<number, 3> result_270 = this->gen_01_counter_269_next(lt_263_268, Rst_243_242, int_249_248);
            counter_266 = result_270[2];
            counter_265 = result_270[1];
            counter_264 = result_270[0];
            number eq_267_271 = counter_264 == clamp_248_247;
            number delta_268_273 = this->gen_01_delta_272_next(eq_267_271);
            number eq_269_274 = delta_268_273 == 1;
            number gen_270_275 = eq_269_274;
            number latch_271_277 = this->gen_01_latch_276_next(mstosamps_255_257, eq_269_274);
            number latch_272_279 = this->gen_01_latch_278_next(noise_252_254, eq_269_274);
            number mul_273_280 = latch_272_279 * 0.5;
            number mul_274_281 = mul_273_280 * slide_251_251;
            number add_275_282 = mul_274_281 + 0.5;
            number sqrt_276_283 = (add_275_282 <= 0 ? 0 : rnbo_sqrt(add_275_282));
            number rsub_277_284 = 1 - add_275_282;
            number sqrt_278_285 = (rsub_277_284 <= 0 ? 0 : rnbo_sqrt(rsub_277_284));
            number counter_279 = 0;
            number counter_280 = 0;
            number counter_281 = 0;
            array<number, 3> result_287 = this->gen_01_counter_286_next(int_253_255, eq_269_274, 0);
            counter_281 = result_287[2];
            counter_280 = result_287[1];
            counter_279 = result_287[0];
            auto min_282_288 = this->minimum(counter_279, latch_271_277);
            number div_283_289 = (latch_271_277 == 0. ? 0. : min_282_288 / latch_271_277);
            number mul_284_290 = div_283_289 * 6.28318530717958647692;
            number cos_285_291 = rnbo_cos(mul_284_290);
            number mul_286_292 = cos_285_291 * 0.5;
            number sub_287_293 = float_247_246 - mul_286_292;
            number gen_288_294 = sub_287_293;
            number noise_289_296 = this->gen_01_noise_295_next();
            number noise_290_298 = this->gen_01_noise_297_next();
            number abs_291_299 = rnbo_abs(noise_290_298);
            number slide_293_302 = this->gen_01_slide_301_next(clamp_292_300, this->sr / (number)100, this->sr / (number)100);
            number mul_294_303 = abs_291_299 * slide_293_302;
            auto scale_300_309 = this->scale(mul_294_303, 0, 1, 0, sub_299_308, 1);
            number slide_302_312 = this->gen_01_slide_311_next(scale_301_310, this->sr / (number)100, this->sr / (number)100);
            number add_303_313 = slide_302_312 + scale_300_309;
            number latch_304_315 = this->gen_01_latch_314_next(add_303_313, eq_269_274);
            number slide_306_318 = this->gen_01_slide_317_next(clamp_305_316, this->sr / (number)100, this->sr / (number)100);
            number mul_307_319 = noise_289_296 * slide_306_318;
            number pow_308_320 = fixnan(rnbo_pow(int_257_259, mul_307_319));
            number slide_310_323 = this->gen_01_slide_322_next(clamp_309_321, this->sr / (number)100, this->sr / (number)100);
            number round_311_324 = rnbo_fround(slide_310_323 * 1 / (number)1) * 1;
            number div_312_325 = round_311_324 / (number)12;
            number pow_313_326 = fixnan(rnbo_pow(int_256_258, div_312_325));
            number mul_314_327 = pow_313_326 * pow_308_320;
            number latch_315_329 = this->gen_01_latch_328_next(mul_314_327, eq_269_274);
            number mul_316_330 = min_282_288 * latch_315_329;
            number add_317_331 = mul_316_330 + latch_304_315;
            number sample_sample_318 = 0;
            number index_sample_319 = 0;
            auto result_332 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_317_331, 0);
            index_sample_319 = result_332[1];
            sample_sample_318 = result_332[0];
            number mul_320_333 = sample_sample_318 * sub_287_293;
            number mul_321_334 = mul_320_333 * sqrt_278_285;
            number gen_322_335 = mul_321_334;
            number mul_323_336 = mul_320_333 * sqrt_276_283;
            number gen_324_337 = mul_323_336;
            number float_329_342 = float(0.5);
            number slide_333_347 = this->gen_01_slide_346_next(clamp_332_345, this->sr / (number)100, this->sr / (number)100);
            number noise_334_349 = this->gen_01_noise_348_next();
            number slide_339_355 = this->gen_01_slide_354_next(clamp_338_353, this->sr / (number)100, this->sr / (number)100);
            number phasor_340_357 = this->gen_01_phasor_356_next(slide_339_355, 0);
            number delta_341_359 = this->gen_01_delta_358_next(phasor_340_357);
            number lt_342_360 = delta_341_359 < 0;
            number counter_343 = 0;
            number counter_344 = 0;
            number counter_345 = 0;
            array<number, 3> result_362 = this->gen_01_counter_361_next(lt_342_360, Rst_325_338, int_331_344);
            counter_345 = result_362[2];
            counter_344 = result_362[1];
            counter_343 = result_362[0];
            number eq_346_363 = counter_343 == clamp_330_343;
            number delta_347_365 = this->gen_01_delta_364_next(eq_346_363);
            number eq_348_366 = delta_347_365 == 1;
            number gen_349_367 = eq_348_366;
            number latch_350_369 = this->gen_01_latch_368_next(mstosamps_337_352, eq_348_366);
            number latch_351_371 = this->gen_01_latch_370_next(noise_334_349, eq_348_366);
            number mul_352_372 = latch_351_371 * 0.5;
            number mul_353_373 = mul_352_372 * slide_333_347;
            number add_354_374 = mul_353_373 + 0.5;
            number sqrt_355_375 = (add_354_374 <= 0 ? 0 : rnbo_sqrt(add_354_374));
            number rsub_356_376 = 1 - add_354_374;
            number sqrt_357_377 = (rsub_356_376 <= 0 ? 0 : rnbo_sqrt(rsub_356_376));
            number counter_358 = 0;
            number counter_359 = 0;
            number counter_360 = 0;
            array<number, 3> result_379 = this->gen_01_counter_378_next(int_335_350, eq_348_366, 0);
            counter_360 = result_379[2];
            counter_359 = result_379[1];
            counter_358 = result_379[0];
            auto min_361_380 = this->minimum(counter_358, latch_350_369);
            number div_362_381 = (latch_350_369 == 0. ? 0. : min_361_380 / latch_350_369);
            number mul_363_382 = div_362_381 * 6.28318530717958647692;
            number cos_364_383 = rnbo_cos(mul_363_382);
            number mul_365_384 = cos_364_383 * 0.5;
            number sub_366_385 = float_329_342 - mul_365_384;
            number gen_367_386 = sub_366_385;
            number noise_371_391 = this->gen_01_noise_390_next();
            number noise_372_393 = this->gen_01_noise_392_next();
            number abs_373_394 = rnbo_abs(noise_372_393);
            number slide_375_397 = this->gen_01_slide_396_next(clamp_374_395, this->sr / (number)100, this->sr / (number)100);
            number mul_376_398 = abs_373_394 * slide_375_397;
            auto scale_382_404 = this->scale(mul_376_398, 0, 1, 0, sub_381_403, 1);
            number slide_384_407 = this->gen_01_slide_406_next(scale_383_405, this->sr / (number)100, this->sr / (number)100);
            number add_385_408 = slide_384_407 + scale_382_404;
            number latch_386_410 = this->gen_01_latch_409_next(add_385_408, eq_348_366);
            number slide_388_413 = this->gen_01_slide_412_next(clamp_387_411, this->sr / (number)100, this->sr / (number)100);
            number mul_389_414 = noise_371_391 * slide_388_413;
            number pow_390_415 = fixnan(rnbo_pow(int_369_388, mul_389_414));
            number slide_392_418 = this->gen_01_slide_417_next(clamp_391_416, this->sr / (number)100, this->sr / (number)100);
            number round_393_419 = rnbo_fround(slide_392_418 * 1 / (number)1) * 1;
            number div_394_420 = round_393_419 / (number)12;
            number pow_395_421 = fixnan(rnbo_pow(int_368_387, div_394_420));
            number mul_396_422 = pow_395_421 * pow_390_415;
            number latch_397_424 = this->gen_01_latch_423_next(mul_396_422, eq_348_366);
            number mul_398_425 = min_361_380 * latch_397_424;
            number add_399_426 = mul_398_425 + latch_386_410;
            number sample_sample_400 = 0;
            number index_sample_401 = 0;
            auto result_427 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_399_426, 0);
            index_sample_401 = result_427[1];
            sample_sample_400 = result_427[0];
            number mul_402_428 = sample_sample_400 * sub_366_385;
            number mul_403_429 = mul_402_428 * sqrt_355_375;
            number gen_404_430 = mul_403_429;
            number mul_405_431 = mul_402_428 * sqrt_357_377;
            number gen_406_432 = mul_405_431;
            number float_411_437 = float(0.5);
            number slide_415_442 = this->gen_01_slide_441_next(clamp_414_440, this->sr / (number)100, this->sr / (number)100);
            number noise_416_444 = this->gen_01_noise_443_next();
            number slide_424_453 = this->gen_01_slide_452_next(clamp_423_451, this->sr / (number)100, this->sr / (number)100);
            number phasor_425_455 = this->gen_01_phasor_454_next(slide_424_453, 0);
            number delta_426_457 = this->gen_01_delta_456_next(phasor_425_455);
            number lt_427_458 = delta_426_457 < 0;
            number counter_428 = 0;
            number counter_429 = 0;
            number counter_430 = 0;
            array<number, 3> result_460 = this->gen_01_counter_459_next(lt_427_458, Rst_407_433, int_413_439);
            counter_430 = result_460[2];
            counter_429 = result_460[1];
            counter_428 = result_460[0];
            number eq_431_461 = counter_428 == clamp_412_438;
            number delta_432_463 = this->gen_01_delta_462_next(eq_431_461);
            number eq_433_464 = delta_432_463 == 1;
            number gen_434_465 = eq_433_464;
            number latch_435_467 = this->gen_01_latch_466_next(mstosamps_419_447, eq_433_464);
            number latch_436_470 = this->gen_01_latch_469_next(noise_416_444, eq_433_464);
            number mul_437_471 = latch_436_470 * 0.5;
            number mul_438_472 = mul_437_471 * slide_415_442;
            number add_439_473 = mul_438_472 + 0.5;
            number sqrt_440_474 = (add_439_473 <= 0 ? 0 : rnbo_sqrt(add_439_473));
            number rsub_441_475 = 1 - add_439_473;
            number sqrt_442_476 = (rsub_441_475 <= 0 ? 0 : rnbo_sqrt(rsub_441_475));
            number counter_443 = 0;
            number counter_444 = 0;
            number counter_445 = 0;
            array<number, 3> result_478 = this->gen_01_counter_477_next(int_417_445, eq_433_464, 0);
            counter_445 = result_478[2];
            counter_444 = result_478[1];
            counter_443 = result_478[0];
            auto min_446_479 = this->minimum(counter_443, latch_435_467);
            number div_447_480 = (latch_435_467 == 0. ? 0. : min_446_479 / latch_435_467);
            number mul_448_481 = div_447_480 * 6.28318530717958647692;
            number cos_449_482 = rnbo_cos(mul_448_481);
            number mul_450_483 = cos_449_482 * 0.5;
            number sub_451_484 = float_411_437 - mul_450_483;
            number gen_452_485 = sub_451_484;
            number noise_453_487 = this->gen_01_noise_486_next();
            number noise_454_489 = this->gen_01_noise_488_next();
            number abs_455_490 = rnbo_abs(noise_454_489);
            number slide_457_493 = this->gen_01_slide_492_next(clamp_456_491, this->sr / (number)100, this->sr / (number)100);
            number mul_458_494 = abs_455_490 * slide_457_493;
            auto scale_464_500 = this->scale(mul_458_494, 0, 1, 0, sub_463_499, 1);
            number slide_466_503 = this->gen_01_slide_502_next(scale_465_501, this->sr / (number)100, this->sr / (number)100);
            number add_467_504 = slide_466_503 + scale_464_500;
            number latch_468_506 = this->gen_01_latch_505_next(add_467_504, eq_433_464);
            number slide_470_509 = this->gen_01_slide_508_next(clamp_469_507, this->sr / (number)100, this->sr / (number)100);
            number mul_471_510 = noise_453_487 * slide_470_509;
            number pow_472_511 = fixnan(rnbo_pow(int_421_449, mul_471_510));
            number slide_474_514 = this->gen_01_slide_513_next(clamp_473_512, this->sr / (number)100, this->sr / (number)100);
            number round_475_515 = rnbo_fround(slide_474_514 * 1 / (number)1) * 1;
            number div_476_516 = round_475_515 / (number)12;
            number pow_477_517 = fixnan(rnbo_pow(int_420_448, div_476_516));
            number mul_478_518 = pow_477_517 * pow_472_511;
            number latch_479_520 = this->gen_01_latch_519_next(mul_478_518, eq_433_464);
            number mul_480_521 = min_446_479 * latch_479_520;
            number add_481_522 = mul_480_521 + latch_468_506;
            number sample_sample_482 = 0;
            number index_sample_483 = 0;
            auto result_523 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_481_522, 0);
            index_sample_483 = result_523[1];
            sample_sample_482 = result_523[0];
            number mul_484_524 = sample_sample_482 * sub_451_484;
            number mul_485_525 = mul_484_524 * sqrt_442_476;
            number gen_486_526 = mul_485_525;
            number mul_487_527 = mul_484_524 * sqrt_440_474;
            number gen_488_528 = mul_487_527;
            number float_493_533 = float(0.5);
            number slide_497_538 = this->gen_01_slide_537_next(clamp_496_536, this->sr / (number)100, this->sr / (number)100);
            number noise_498_540 = this->gen_01_noise_539_next();
            number slide_506_550 = this->gen_01_slide_549_next(clamp_505_547, this->sr / (number)100, this->sr / (number)100);
            number phasor_507_552 = this->gen_01_phasor_551_next(slide_506_550, 0);
            number delta_508_554 = this->gen_01_delta_553_next(phasor_507_552);
            number lt_509_555 = delta_508_554 < 0;
            number counter_510 = 0;
            number counter_511 = 0;
            number counter_512 = 0;
            array<number, 3> result_557 = this->gen_01_counter_556_next(lt_509_555, Rst_489_529, int_495_535);
            counter_512 = result_557[2];
            counter_511 = result_557[1];
            counter_510 = result_557[0];
            number eq_513_558 = counter_510 == clamp_494_534;
            number delta_514_560 = this->gen_01_delta_559_next(eq_513_558);
            number eq_515_561 = delta_514_560 == 1;
            number gen_516_562 = eq_515_561;
            number latch_517_564 = this->gen_01_latch_563_next(noise_498_540, eq_515_561);
            number mul_518_565 = latch_517_564 * 0.5;
            number mul_519_566 = mul_518_565 * slide_497_538;
            number add_520_567 = mul_519_566 + 0.5;
            number sqrt_521_568 = (add_520_567 <= 0 ? 0 : rnbo_sqrt(add_520_567));
            number rsub_522_569 = 1 - add_520_567;
            number sqrt_523_570 = (rsub_522_569 <= 0 ? 0 : rnbo_sqrt(rsub_522_569));
            number latch_524_572 = this->gen_01_latch_571_next(mstosamps_501_543, eq_515_561);
            number counter_525 = 0;
            number counter_526 = 0;
            number counter_527 = 0;
            array<number, 3> result_574 = this->gen_01_counter_573_next(int_499_541, eq_515_561, 0);
            counter_527 = result_574[2];
            counter_526 = result_574[1];
            counter_525 = result_574[0];
            auto min_528_575 = this->minimum(counter_525, latch_524_572);
            number div_529_576 = (latch_524_572 == 0. ? 0. : min_528_575 / latch_524_572);
            number mul_530_577 = div_529_576 * 6.28318530717958647692;
            number cos_531_578 = rnbo_cos(mul_530_577);
            number mul_532_579 = cos_531_578 * 0.5;
            number sub_533_580 = float_493_533 - mul_532_579;
            number gen_534_581 = sub_533_580;
            number noise_535_583 = this->gen_01_noise_582_next();
            number noise_536_585 = this->gen_01_noise_584_next();
            number abs_537_586 = rnbo_abs(noise_536_585);
            number slide_539_589 = this->gen_01_slide_588_next(clamp_538_587, this->sr / (number)100, this->sr / (number)100);
            number mul_540_590 = abs_537_586 * slide_539_589;
            auto scale_546_596 = this->scale(mul_540_590, 0, 1, 0, sub_545_595, 1);
            number slide_548_599 = this->gen_01_slide_598_next(scale_547_597, this->sr / (number)100, this->sr / (number)100);
            number add_549_600 = slide_548_599 + scale_546_596;
            number latch_550_602 = this->gen_01_latch_601_next(add_549_600, eq_515_561);
            number slide_552_605 = this->gen_01_slide_604_next(clamp_551_603, this->sr / (number)100, this->sr / (number)100);
            number mul_553_606 = noise_535_583 * slide_552_605;
            number pow_554_607 = fixnan(rnbo_pow(int_503_545, mul_553_606));
            number slide_556_610 = this->gen_01_slide_609_next(clamp_555_608, this->sr / (number)100, this->sr / (number)100);
            number round_557_611 = rnbo_fround(slide_556_610 * 1 / (number)1) * 1;
            number div_558_612 = round_557_611 / (number)12;
            number pow_559_613 = fixnan(rnbo_pow(int_502_544, div_558_612));
            number mul_560_614 = pow_559_613 * pow_554_607;
            number latch_561_616 = this->gen_01_latch_615_next(mul_560_614, eq_515_561);
            number mul_562_617 = min_528_575 * latch_561_616;
            number add_563_618 = mul_562_617 + latch_550_602;
            number sample_sample_564 = 0;
            number index_sample_565 = 0;
            auto result_619 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_563_618, 0);
            index_sample_565 = result_619[1];
            sample_sample_564 = result_619[0];
            number mul_566_620 = sample_sample_564 * sub_533_580;
            number mul_567_621 = mul_566_620 * sqrt_523_570;
            number gen_568_622 = mul_567_621;
            number mul_569_623 = mul_566_620 * sqrt_521_568;
            number gen_570_624 = mul_569_623;
            number float_575_629 = float(0.5);
            number slide_579_634 = this->gen_01_slide_633_next(clamp_578_632, this->sr / (number)100, this->sr / (number)100);
            number noise_580_636 = this->gen_01_noise_635_next();
            number slide_585_642 = this->gen_01_slide_641_next(clamp_584_640, this->sr / (number)100, this->sr / (number)100);
            number phasor_586_644 = this->gen_01_phasor_643_next(slide_585_642, 0);
            number delta_587_646 = this->gen_01_delta_645_next(phasor_586_644);
            number lt_588_647 = delta_587_646 < 0;
            number counter_589 = 0;
            number counter_590 = 0;
            number counter_591 = 0;
            array<number, 3> result_649 = this->gen_01_counter_648_next(lt_588_647, Rst_571_625, int_577_631);
            counter_591 = result_649[2];
            counter_590 = result_649[1];
            counter_589 = result_649[0];
            number eq_592_650 = counter_589 == clamp_576_630;
            number delta_593_652 = this->gen_01_delta_651_next(eq_592_650);
            number eq_594_653 = delta_593_652 == 1;
            number gen_595_654 = eq_594_653;
            number latch_596_656 = this->gen_01_latch_655_next(mstosamps_583_639, eq_594_653);
            number latch_597_658 = this->gen_01_latch_657_next(noise_580_636, eq_594_653);
            number mul_598_659 = latch_597_658 * 0.5;
            number mul_599_660 = mul_598_659 * slide_579_634;
            number add_600_661 = mul_599_660 + 0.5;
            number sqrt_601_662 = (add_600_661 <= 0 ? 0 : rnbo_sqrt(add_600_661));
            number rsub_602_663 = 1 - add_600_661;
            number sqrt_603_664 = (rsub_602_663 <= 0 ? 0 : rnbo_sqrt(rsub_602_663));
            number counter_604 = 0;
            number counter_605 = 0;
            number counter_606 = 0;
            array<number, 3> result_666 = this->gen_01_counter_665_next(int_581_637, eq_594_653, 0);
            counter_606 = result_666[2];
            counter_605 = result_666[1];
            counter_604 = result_666[0];
            auto min_607_667 = this->minimum(counter_604, latch_596_656);
            number div_608_668 = (latch_596_656 == 0. ? 0. : min_607_667 / latch_596_656);
            number mul_609_669 = div_608_668 * 6.28318530717958647692;
            number cos_610_670 = rnbo_cos(mul_609_669);
            number mul_611_671 = cos_610_670 * 0.5;
            number sub_612_672 = float_575_629 - mul_611_671;
            number gen_613_673 = sub_612_672;
            number noise_617_678 = this->gen_01_noise_677_next();
            number noise_618_680 = this->gen_01_noise_679_next();
            number abs_619_681 = rnbo_abs(noise_618_680);
            number slide_621_684 = this->gen_01_slide_683_next(clamp_620_682, this->sr / (number)100, this->sr / (number)100);
            number mul_622_685 = abs_619_681 * slide_621_684;
            auto scale_628_691 = this->scale(mul_622_685, 0, 1, 0, sub_627_690, 1);
            number slide_630_694 = this->gen_01_slide_693_next(scale_629_692, this->sr / (number)100, this->sr / (number)100);
            number add_631_695 = slide_630_694 + scale_628_691;
            number latch_632_697 = this->gen_01_latch_696_next(add_631_695, eq_594_653);
            number slide_634_700 = this->gen_01_slide_699_next(clamp_633_698, this->sr / (number)100, this->sr / (number)100);
            number mul_635_701 = noise_617_678 * slide_634_700;
            number pow_636_702 = fixnan(rnbo_pow(int_615_675, mul_635_701));
            number slide_638_705 = this->gen_01_slide_704_next(clamp_637_703, this->sr / (number)100, this->sr / (number)100);
            number round_639_706 = rnbo_fround(slide_638_705 * 1 / (number)1) * 1;
            number div_640_707 = round_639_706 / (number)12;
            number pow_641_708 = fixnan(rnbo_pow(int_614_674, div_640_707));
            number mul_642_709 = pow_641_708 * pow_636_702;
            number latch_643_711 = this->gen_01_latch_710_next(mul_642_709, eq_594_653);
            number mul_644_712 = min_607_667 * latch_643_711;
            number add_645_713 = mul_644_712 + latch_632_697;
            number sample_sample_646 = 0;
            number index_sample_647 = 0;
            auto result_714 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_645_713, 0);
            index_sample_647 = result_714[1];
            sample_sample_646 = result_714[0];
            number mul_648_715 = sample_sample_646 * sub_612_672;
            number mul_649_716 = mul_648_715 * sqrt_603_664;
            number gen_650_717 = mul_649_716;
            number mul_651_718 = mul_648_715 * sqrt_601_662;
            number gen_652_719 = mul_651_718;
            number float_657_724 = float(0.5);
            number slide_661_729 = this->gen_01_slide_728_next(clamp_660_727, this->sr / (number)100, this->sr / (number)100);
            number noise_662_731 = this->gen_01_noise_730_next();
            number slide_670_740 = this->gen_01_slide_739_next(clamp_669_738, this->sr / (number)100, this->sr / (number)100);
            number phasor_671_742 = this->gen_01_phasor_741_next(slide_670_740, 0);
            number delta_672_744 = this->gen_01_delta_743_next(phasor_671_742);
            number lt_673_745 = delta_672_744 < 0;
            number counter_674 = 0;
            number counter_675 = 0;
            number counter_676 = 0;
            array<number, 3> result_747 = this->gen_01_counter_746_next(lt_673_745, Rst_653_720, int_659_726);
            counter_676 = result_747[2];
            counter_675 = result_747[1];
            counter_674 = result_747[0];
            number eq_677_748 = counter_674 == clamp_658_725;
            number delta_678_750 = this->gen_01_delta_749_next(eq_677_748);
            number eq_679_751 = delta_678_750 == 1;
            number gen_680_752 = eq_679_751;
            number latch_681_754 = this->gen_01_latch_753_next(mstosamps_665_734, eq_679_751);
            number latch_682_756 = this->gen_01_latch_755_next(noise_662_731, eq_679_751);
            number mul_683_757 = latch_682_756 * 0.5;
            number mul_684_758 = mul_683_757 * slide_661_729;
            number add_685_759 = mul_684_758 + 0.5;
            number sqrt_686_760 = (add_685_759 <= 0 ? 0 : rnbo_sqrt(add_685_759));
            number rsub_687_761 = 1 - add_685_759;
            number sqrt_688_762 = (rsub_687_761 <= 0 ? 0 : rnbo_sqrt(rsub_687_761));
            number counter_689 = 0;
            number counter_690 = 0;
            number counter_691 = 0;
            array<number, 3> result_764 = this->gen_01_counter_763_next(int_663_732, eq_679_751, 0);
            counter_691 = result_764[2];
            counter_690 = result_764[1];
            counter_689 = result_764[0];
            auto min_692_765 = this->minimum(counter_689, latch_681_754);
            number div_693_766 = (latch_681_754 == 0. ? 0. : min_692_765 / latch_681_754);
            number mul_694_767 = div_693_766 * 6.28318530717958647692;
            number cos_695_768 = rnbo_cos(mul_694_767);
            number mul_696_769 = cos_695_768 * 0.5;
            number sub_697_770 = float_657_724 - mul_696_769;
            number gen_698_771 = sub_697_770;
            number noise_699_773 = this->gen_01_noise_772_next();
            number noise_700_775 = this->gen_01_noise_774_next();
            number abs_701_776 = rnbo_abs(noise_700_775);
            number slide_703_779 = this->gen_01_slide_778_next(clamp_702_777, this->sr / (number)100, this->sr / (number)100);
            number mul_704_780 = abs_701_776 * slide_703_779;
            auto scale_710_786 = this->scale(mul_704_780, 0, 1, 0, sub_709_785, 1);
            number slide_712_789 = this->gen_01_slide_788_next(scale_711_787, this->sr / (number)100, this->sr / (number)100);
            number add_713_790 = slide_712_789 + scale_710_786;
            number latch_714_792 = this->gen_01_latch_791_next(add_713_790, eq_679_751);
            number slide_716_796 = this->gen_01_slide_795_next(clamp_715_793, this->sr / (number)100, this->sr / (number)100);
            number mul_717_797 = noise_699_773 * slide_716_796;
            number pow_718_798 = fixnan(rnbo_pow(int_667_736, mul_717_797));
            number slide_720_801 = this->gen_01_slide_800_next(clamp_719_799, this->sr / (number)100, this->sr / (number)100);
            number round_721_802 = rnbo_fround(slide_720_801 * 1 / (number)1) * 1;
            number div_722_803 = round_721_802 / (number)12;
            number pow_723_804 = fixnan(rnbo_pow(int_666_735, div_722_803));
            number mul_724_805 = pow_723_804 * pow_718_798;
            number latch_725_807 = this->gen_01_latch_806_next(mul_724_805, eq_679_751);
            number mul_726_808 = min_692_765 * latch_725_807;
            number add_727_809 = mul_726_808 + latch_714_792;
            number sample_sample_728 = 0;
            number index_sample_729 = 0;
            auto result_810 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_727_809, 0);
            index_sample_729 = result_810[1];
            sample_sample_728 = result_810[0];
            number mul_730_811 = sample_sample_728 * sub_697_770;
            number mul_731_812 = mul_730_811 * sqrt_688_762;
            number gen_732_813 = mul_731_812;
            number mul_733_814 = mul_730_811 * sqrt_686_760;
            number gen_734_815 = mul_733_814;
            number float_739_820 = float(0.5);
            number slide_743_825 = this->gen_01_slide_824_next(clamp_742_823, this->sr / (number)100, this->sr / (number)100);
            number noise_744_828 = this->gen_01_noise_827_next();
            number slide_752_837 = this->gen_01_slide_836_next(clamp_751_835, this->sr / (number)100, this->sr / (number)100);
            number phasor_753_839 = this->gen_01_phasor_838_next(slide_752_837, 0);
            number delta_754_841 = this->gen_01_delta_840_next(phasor_753_839);
            number lt_755_842 = delta_754_841 < 0;
            number counter_756 = 0;
            number counter_757 = 0;
            number counter_758 = 0;
            array<number, 3> result_844 = this->gen_01_counter_843_next(lt_755_842, Rst_735_816, int_741_822);
            counter_758 = result_844[2];
            counter_757 = result_844[1];
            counter_756 = result_844[0];
            number eq_759_845 = counter_756 == clamp_740_821;
            number delta_760_847 = this->gen_01_delta_846_next(eq_759_845);
            number eq_761_848 = delta_760_847 == 1;
            number gen_762_849 = eq_761_848;
            number latch_763_851 = this->gen_01_latch_850_next(mstosamps_747_831, eq_761_848);
            number latch_764_853 = this->gen_01_latch_852_next(noise_744_828, eq_761_848);
            number mul_765_854 = latch_764_853 * 0.5;
            number mul_766_855 = mul_765_854 * slide_743_825;
            number add_767_856 = mul_766_855 + 0.5;
            number sqrt_768_857 = (add_767_856 <= 0 ? 0 : rnbo_sqrt(add_767_856));
            number rsub_769_858 = 1 - add_767_856;
            number sqrt_770_859 = (rsub_769_858 <= 0 ? 0 : rnbo_sqrt(rsub_769_858));
            number counter_771 = 0;
            number counter_772 = 0;
            number counter_773 = 0;
            array<number, 3> result_861 = this->gen_01_counter_860_next(int_745_829, eq_761_848, 0);
            counter_773 = result_861[2];
            counter_772 = result_861[1];
            counter_771 = result_861[0];
            auto min_774_862 = this->minimum(counter_771, latch_763_851);
            number div_775_863 = (latch_763_851 == 0. ? 0. : min_774_862 / latch_763_851);
            number mul_776_864 = div_775_863 * 6.28318530717958647692;
            number cos_777_865 = rnbo_cos(mul_776_864);
            number mul_778_866 = cos_777_865 * 0.5;
            number sub_779_867 = float_739_820 - mul_778_866;
            number gen_780_868 = sub_779_867;
            number noise_781_870 = this->gen_01_noise_869_next();
            number noise_782_872 = this->gen_01_noise_871_next();
            number abs_783_873 = rnbo_abs(noise_782_872);
            number slide_785_876 = this->gen_01_slide_875_next(clamp_784_874, this->sr / (number)100, this->sr / (number)100);
            number mul_786_877 = abs_783_873 * slide_785_876;
            auto scale_792_883 = this->scale(mul_786_877, 0, 1, 0, sub_791_882, 1);
            number slide_794_886 = this->gen_01_slide_885_next(scale_793_884, this->sr / (number)100, this->sr / (number)100);
            number add_795_887 = slide_794_886 + scale_792_883;
            number latch_796_889 = this->gen_01_latch_888_next(add_795_887, eq_761_848);
            number slide_798_892 = this->gen_01_slide_891_next(clamp_797_890, this->sr / (number)100, this->sr / (number)100);
            number mul_799_893 = noise_781_870 * slide_798_892;
            number pow_800_894 = fixnan(rnbo_pow(int_749_833, mul_799_893));
            number slide_802_897 = this->gen_01_slide_896_next(clamp_801_895, this->sr / (number)100, this->sr / (number)100);
            number round_803_898 = rnbo_fround(slide_802_897 * 1 / (number)1) * 1;
            number div_804_899 = round_803_898 / (number)12;
            number pow_805_900 = fixnan(rnbo_pow(int_748_832, div_804_899));
            number mul_806_901 = pow_805_900 * pow_800_894;
            number latch_807_903 = this->gen_01_latch_902_next(mul_806_901, eq_761_848);
            number mul_808_904 = min_774_862 * latch_807_903;
            number add_809_905 = mul_808_904 + latch_796_889;
            number sample_sample_810 = 0;
            number index_sample_811 = 0;
            auto result_906 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_809_905, 0);
            index_sample_811 = result_906[1];
            sample_sample_810 = result_906[0];
            number mul_812_907 = sample_sample_810 * sub_779_867;
            number mul_813_908 = mul_812_907 * sqrt_770_859;
            number gen_814_909 = mul_813_908;
            number mul_815_910 = mul_812_907 * sqrt_768_857;
            number gen_816_911 = mul_815_910;
            number float_821_916 = float(0.5);
            number slide_825_921 = this->gen_01_slide_920_next(clamp_824_919, this->sr / (number)100, this->sr / (number)100);
            number noise_826_923 = this->gen_01_noise_922_next();
            number slide_834_932 = this->gen_01_slide_931_next(clamp_833_930, this->sr / (number)100, this->sr / (number)100);
            number phasor_835_934 = this->gen_01_phasor_933_next(slide_834_932, 0);
            number delta_836_936 = this->gen_01_delta_935_next(phasor_835_934);
            number lt_837_937 = delta_836_936 < 0;
            number counter_838 = 0;
            number counter_839 = 0;
            number counter_840 = 0;
            array<number, 3> result_939 = this->gen_01_counter_938_next(lt_837_937, Rst_817_912, int_823_918);
            counter_840 = result_939[2];
            counter_839 = result_939[1];
            counter_838 = result_939[0];
            number eq_841_940 = counter_838 == clamp_822_917;
            number delta_842_942 = this->gen_01_delta_941_next(eq_841_940);
            number eq_843_943 = delta_842_942 == 1;
            number gen_844_944 = eq_843_943;
            number latch_845_946 = this->gen_01_latch_945_next(mstosamps_829_926, eq_843_943);
            number latch_846_948 = this->gen_01_latch_947_next(noise_826_923, eq_843_943);
            number mul_847_949 = latch_846_948 * 0.5;
            number mul_848_950 = mul_847_949 * slide_825_921;
            number add_849_951 = mul_848_950 + 0.5;
            number sqrt_850_952 = (add_849_951 <= 0 ? 0 : rnbo_sqrt(add_849_951));
            number rsub_851_953 = 1 - add_849_951;
            number sqrt_852_954 = (rsub_851_953 <= 0 ? 0 : rnbo_sqrt(rsub_851_953));
            number counter_853 = 0;
            number counter_854 = 0;
            number counter_855 = 0;
            array<number, 3> result_956 = this->gen_01_counter_955_next(int_827_924, eq_843_943, 0);
            counter_855 = result_956[2];
            counter_854 = result_956[1];
            counter_853 = result_956[0];
            auto min_856_957 = this->minimum(counter_853, latch_845_946);
            number div_857_958 = (latch_845_946 == 0. ? 0. : min_856_957 / latch_845_946);
            number mul_858_959 = div_857_958 * 6.28318530717958647692;
            number cos_859_960 = rnbo_cos(mul_858_959);
            number mul_860_961 = cos_859_960 * 0.5;
            number sub_861_962 = float_821_916 - mul_860_961;
            number gen_862_963 = sub_861_962;
            number noise_863_965 = this->gen_01_noise_964_next();
            number noise_864_967 = this->gen_01_noise_966_next();
            number abs_865_968 = rnbo_abs(noise_864_967);
            number slide_867_971 = this->gen_01_slide_970_next(clamp_866_969, this->sr / (number)100, this->sr / (number)100);
            number mul_868_972 = abs_865_968 * slide_867_971;
            auto scale_874_978 = this->scale(mul_868_972, 0, 1, 0, sub_873_977, 1);
            number slide_876_981 = this->gen_01_slide_980_next(scale_875_979, this->sr / (number)100, this->sr / (number)100);
            number add_877_982 = slide_876_981 + scale_874_978;
            number latch_878_984 = this->gen_01_latch_983_next(add_877_982, eq_843_943);
            number slide_880_987 = this->gen_01_slide_986_next(clamp_879_985, this->sr / (number)100, this->sr / (number)100);
            number mul_881_988 = noise_863_965 * slide_880_987;
            number pow_882_989 = fixnan(rnbo_pow(int_831_928, mul_881_988));
            number slide_884_992 = this->gen_01_slide_991_next(clamp_883_990, this->sr / (number)100, this->sr / (number)100);
            number round_885_993 = rnbo_fround(slide_884_992 * 1 / (number)1) * 1;
            number div_886_994 = round_885_993 / (number)12;
            number pow_887_995 = fixnan(rnbo_pow(int_830_927, div_886_994));
            number mul_888_996 = pow_887_995 * pow_882_989;
            number latch_889_998 = this->gen_01_latch_997_next(mul_888_996, eq_843_943);
            number mul_890_999 = min_856_957 * latch_889_998;
            number add_891_1000 = mul_890_999 + latch_878_984;
            number sample_sample_892 = 0;
            number index_sample_893 = 0;
            auto result_1001 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_891_1000, 0);
            index_sample_893 = result_1001[1];
            sample_sample_892 = result_1001[0];
            number mul_894_1002 = sample_sample_892 * sub_861_962;
            number mul_895_1003 = mul_894_1002 * sqrt_852_954;
            number gen_896_1004 = mul_895_1003;
            number mul_897_1005 = mul_894_1002 * sqrt_850_952;
            number gen_898_1006 = mul_897_1005;
            number float_903_1011 = float(0.5);
            number slide_907_1016 = this->gen_01_slide_1015_next(clamp_906_1014, this->sr / (number)100, this->sr / (number)100);
            number noise_908_1018 = this->gen_01_noise_1017_next();
            number slide_913_1024 = this->gen_01_slide_1023_next(clamp_912_1022, this->sr / (number)100, this->sr / (number)100);
            number phasor_914_1026 = this->gen_01_phasor_1025_next(slide_913_1024, 0);
            number delta_915_1028 = this->gen_01_delta_1027_next(phasor_914_1026);
            number lt_916_1029 = delta_915_1028 < 0;
            number counter_917 = 0;
            number counter_918 = 0;
            number counter_919 = 0;
            array<number, 3> result_1031 = this->gen_01_counter_1030_next(lt_916_1029, Rst_899_1007, int_905_1013);
            counter_919 = result_1031[2];
            counter_918 = result_1031[1];
            counter_917 = result_1031[0];
            number eq_920_1032 = counter_917 == clamp_904_1012;
            number delta_921_1034 = this->gen_01_delta_1033_next(eq_920_1032);
            number eq_922_1035 = delta_921_1034 == 1;
            number gen_923_1036 = eq_922_1035;
            number latch_924_1038 = this->gen_01_latch_1037_next(mstosamps_911_1021, eq_922_1035);
            number latch_925_1040 = this->gen_01_latch_1039_next(noise_908_1018, eq_922_1035);
            number mul_926_1041 = latch_925_1040 * 0.5;
            number mul_927_1042 = mul_926_1041 * slide_907_1016;
            number add_928_1043 = mul_927_1042 + 0.5;
            number sqrt_929_1044 = (add_928_1043 <= 0 ? 0 : rnbo_sqrt(add_928_1043));
            number rsub_930_1045 = 1 - add_928_1043;
            number sqrt_931_1046 = (rsub_930_1045 <= 0 ? 0 : rnbo_sqrt(rsub_930_1045));
            number counter_932 = 0;
            number counter_933 = 0;
            number counter_934 = 0;
            array<number, 3> result_1048 = this->gen_01_counter_1047_next(int_909_1019, eq_922_1035, 0);
            counter_934 = result_1048[2];
            counter_933 = result_1048[1];
            counter_932 = result_1048[0];
            auto min_935_1049 = this->minimum(counter_932, latch_924_1038);
            number div_936_1050 = (latch_924_1038 == 0. ? 0. : min_935_1049 / latch_924_1038);
            number mul_937_1051 = div_936_1050 * 6.28318530717958647692;
            number cos_938_1052 = rnbo_cos(mul_937_1051);
            number mul_939_1053 = cos_938_1052 * 0.5;
            number sub_940_1054 = float_903_1011 - mul_939_1053;
            number gen_941_1055 = sub_940_1054;
            number noise_945_1060 = this->gen_01_noise_1059_next();
            number noise_946_1062 = this->gen_01_noise_1061_next();
            number abs_947_1063 = rnbo_abs(noise_946_1062);
            number slide_949_1066 = this->gen_01_slide_1065_next(clamp_948_1064, this->sr / (number)100, this->sr / (number)100);
            number mul_950_1067 = abs_947_1063 * slide_949_1066;
            auto scale_956_1073 = this->scale(mul_950_1067, 0, 1, 0, sub_955_1072, 1);
            number slide_958_1076 = this->gen_01_slide_1075_next(scale_957_1074, this->sr / (number)100, this->sr / (number)100);
            number add_959_1077 = slide_958_1076 + scale_956_1073;
            number latch_960_1079 = this->gen_01_latch_1078_next(add_959_1077, eq_922_1035);
            number slide_962_1082 = this->gen_01_slide_1081_next(clamp_961_1080, this->sr / (number)100, this->sr / (number)100);
            number mul_963_1083 = noise_945_1060 * slide_962_1082;
            number pow_964_1084 = fixnan(rnbo_pow(int_943_1057, mul_963_1083));
            number slide_966_1087 = this->gen_01_slide_1086_next(clamp_965_1085, this->sr / (number)100, this->sr / (number)100);
            number round_967_1088 = rnbo_fround(slide_966_1087 * 1 / (number)1) * 1;
            number div_968_1089 = round_967_1088 / (number)12;
            number pow_969_1090 = fixnan(rnbo_pow(int_942_1056, div_968_1089));
            number mul_970_1091 = pow_969_1090 * pow_964_1084;
            number latch_971_1093 = this->gen_01_latch_1092_next(mul_970_1091, eq_922_1035);
            number mul_972_1094 = min_935_1049 * latch_971_1093;
            number add_973_1095 = mul_972_1094 + latch_960_1079;
            number sample_sample_974 = 0;
            number index_sample_975 = 0;
            auto result_1096 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_973_1095, 0);
            index_sample_975 = result_1096[1];
            sample_sample_974 = result_1096[0];
            number mul_976_1097 = sample_sample_974 * sub_940_1054;
            number mul_977_1098 = mul_976_1097 * sqrt_929_1044;
            number gen_978_1099 = mul_977_1098;
            number mul_979_1100 = mul_976_1097 * sqrt_931_1046;
            number gen_980_1101 = mul_979_1100;
            number float_985_1106 = float(0.5);
            number slide_989_1111 = this->gen_01_slide_1110_next(clamp_988_1109, this->sr / (number)100, this->sr / (number)100);
            number noise_990_1113 = this->gen_01_noise_1112_next();
            number slide_998_1122 = this->gen_01_slide_1121_next(clamp_997_1120, this->sr / (number)100, this->sr / (number)100);
            number phasor_999_1124 = this->gen_01_phasor_1123_next(slide_998_1122, 0);
            number delta_1000_1126 = this->gen_01_delta_1125_next(phasor_999_1124);
            number lt_1001_1127 = delta_1000_1126 < 0;
            number counter_1002 = 0;
            number counter_1003 = 0;
            number counter_1004 = 0;
            array<number, 3> result_1129 = this->gen_01_counter_1128_next(lt_1001_1127, Rst_981_1102, int_987_1108);
            counter_1004 = result_1129[2];
            counter_1003 = result_1129[1];
            counter_1002 = result_1129[0];
            number eq_1005_1130 = counter_1002 == clamp_986_1107;
            number delta_1006_1132 = this->gen_01_delta_1131_next(eq_1005_1130);
            number eq_1007_1133 = delta_1006_1132 == 1;
            number gen_1008_1134 = eq_1007_1133;
            number latch_1009_1137 = this->gen_01_latch_1136_next(noise_990_1113, eq_1007_1133);
            number mul_1010_1138 = latch_1009_1137 * 0.5;
            number mul_1011_1139 = mul_1010_1138 * slide_989_1111;
            number add_1012_1140 = mul_1011_1139 + 0.5;
            number sqrt_1013_1141 = (add_1012_1140 <= 0 ? 0 : rnbo_sqrt(add_1012_1140));
            number rsub_1014_1142 = 1 - add_1012_1140;
            number sqrt_1015_1143 = (rsub_1014_1142 <= 0 ? 0 : rnbo_sqrt(rsub_1014_1142));
            number latch_1016_1145 = this->gen_01_latch_1144_next(mstosamps_993_1116, eq_1007_1133);
            number counter_1017 = 0;
            number counter_1018 = 0;
            number counter_1019 = 0;
            array<number, 3> result_1147 = this->gen_01_counter_1146_next(int_991_1114, eq_1007_1133, 0);
            counter_1019 = result_1147[2];
            counter_1018 = result_1147[1];
            counter_1017 = result_1147[0];
            auto min_1020_1148 = this->minimum(counter_1017, latch_1016_1145);
            number div_1021_1149 = (latch_1016_1145 == 0. ? 0. : min_1020_1148 / latch_1016_1145);
            number mul_1022_1150 = div_1021_1149 * 6.28318530717958647692;
            number cos_1023_1151 = rnbo_cos(mul_1022_1150);
            number mul_1024_1152 = cos_1023_1151 * 0.5;
            number sub_1025_1153 = float_985_1106 - mul_1024_1152;
            number gen_1026_1154 = sub_1025_1153;
            number noise_1027_1156 = this->gen_01_noise_1155_next();
            number noise_1028_1158 = this->gen_01_noise_1157_next();
            number abs_1029_1159 = rnbo_abs(noise_1028_1158);
            number slide_1031_1162 = this->gen_01_slide_1161_next(clamp_1030_1160, this->sr / (number)100, this->sr / (number)100);
            number mul_1032_1163 = abs_1029_1159 * slide_1031_1162;
            auto scale_1038_1169 = this->scale(mul_1032_1163, 0, 1, 0, sub_1037_1168, 1);
            number slide_1040_1172 = this->gen_01_slide_1171_next(scale_1039_1170, this->sr / (number)100, this->sr / (number)100);
            number add_1041_1173 = slide_1040_1172 + scale_1038_1169;
            number latch_1042_1175 = this->gen_01_latch_1174_next(add_1041_1173, eq_1007_1133);
            number slide_1044_1178 = this->gen_01_slide_1177_next(clamp_1043_1176, this->sr / (number)100, this->sr / (number)100);
            number mul_1045_1179 = noise_1027_1156 * slide_1044_1178;
            number pow_1046_1180 = fixnan(rnbo_pow(int_995_1118, mul_1045_1179));
            number slide_1048_1183 = this->gen_01_slide_1182_next(clamp_1047_1181, this->sr / (number)100, this->sr / (number)100);
            number round_1049_1184 = rnbo_fround(slide_1048_1183 * 1 / (number)1) * 1;
            number div_1050_1185 = round_1049_1184 / (number)12;
            number pow_1051_1186 = fixnan(rnbo_pow(int_994_1117, div_1050_1185));
            number mul_1052_1187 = pow_1051_1186 * pow_1046_1180;
            number latch_1053_1189 = this->gen_01_latch_1188_next(mul_1052_1187, eq_1007_1133);
            number mul_1054_1190 = min_1020_1148 * latch_1053_1189;
            number add_1055_1191 = mul_1054_1190 + latch_1042_1175;
            number sample_sample_1056 = 0;
            number index_sample_1057 = 0;
            auto result_1192 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1055_1191, 0);
            index_sample_1057 = result_1192[1];
            sample_sample_1056 = result_1192[0];
            number mul_1058_1193 = sample_sample_1056 * sub_1025_1153;
            number mul_1059_1194 = mul_1058_1193 * sqrt_1013_1141;
            number gen_1060_1195 = mul_1059_1194;
            number mul_1061_1196 = mul_1058_1193 * sqrt_1015_1143;
            number gen_1062_1197 = mul_1061_1196;
            number float_1067_1202 = float(0.5);
            number slide_1071_1207 = this->gen_01_slide_1206_next(clamp_1070_1205, this->sr / (number)100, this->sr / (number)100);
            number noise_1072_1209 = this->gen_01_noise_1208_next();
            number slide_1080_1218 = this->gen_01_slide_1217_next(clamp_1079_1216, this->sr / (number)100, this->sr / (number)100);
            number phasor_1081_1220 = this->gen_01_phasor_1219_next(slide_1080_1218, 0);
            number delta_1082_1222 = this->gen_01_delta_1221_next(phasor_1081_1220);
            number lt_1083_1223 = delta_1082_1222 < 0;
            number counter_1084 = 0;
            number counter_1085 = 0;
            number counter_1086 = 0;
            array<number, 3> result_1225 = this->gen_01_counter_1224_next(lt_1083_1223, Rst_1063_1198, int_1069_1204);
            counter_1086 = result_1225[2];
            counter_1085 = result_1225[1];
            counter_1084 = result_1225[0];
            number eq_1087_1226 = counter_1084 == clamp_1068_1203;
            number delta_1088_1228 = this->gen_01_delta_1227_next(eq_1087_1226);
            number eq_1089_1229 = delta_1088_1228 == 1;
            number gen_1090_1230 = eq_1089_1229;
            number latch_1091_1232 = this->gen_01_latch_1231_next(noise_1072_1209, eq_1089_1229);
            number mul_1092_1233 = latch_1091_1232 * 0.5;
            number mul_1093_1234 = mul_1092_1233 * slide_1071_1207;
            number add_1094_1235 = mul_1093_1234 + 0.5;
            number sqrt_1095_1236 = (add_1094_1235 <= 0 ? 0 : rnbo_sqrt(add_1094_1235));
            number rsub_1096_1237 = 1 - add_1094_1235;
            number sqrt_1097_1238 = (rsub_1096_1237 <= 0 ? 0 : rnbo_sqrt(rsub_1096_1237));
            number latch_1098_1240 = this->gen_01_latch_1239_next(mstosamps_1075_1212, eq_1089_1229);
            number counter_1099 = 0;
            number counter_1100 = 0;
            number counter_1101 = 0;
            array<number, 3> result_1242 = this->gen_01_counter_1241_next(int_1073_1210, eq_1089_1229, 0);
            counter_1101 = result_1242[2];
            counter_1100 = result_1242[1];
            counter_1099 = result_1242[0];
            auto min_1102_1243 = this->minimum(counter_1099, latch_1098_1240);
            number div_1103_1244 = (latch_1098_1240 == 0. ? 0. : min_1102_1243 / latch_1098_1240);
            number mul_1104_1245 = div_1103_1244 * 6.28318530717958647692;
            number cos_1105_1246 = rnbo_cos(mul_1104_1245);
            number mul_1106_1247 = cos_1105_1246 * 0.5;
            number sub_1107_1248 = float_1067_1202 - mul_1106_1247;
            number gen_1108_1249 = sub_1107_1248;
            number noise_1109_1251 = this->gen_01_noise_1250_next();
            number noise_1110_1253 = this->gen_01_noise_1252_next();
            number abs_1111_1254 = rnbo_abs(noise_1110_1253);
            number slide_1113_1257 = this->gen_01_slide_1256_next(clamp_1112_1255, this->sr / (number)100, this->sr / (number)100);
            number mul_1114_1258 = abs_1111_1254 * slide_1113_1257;
            auto scale_1120_1264 = this->scale(mul_1114_1258, 0, 1, 0, sub_1119_1263, 1);
            number slide_1122_1267 = this->gen_01_slide_1266_next(scale_1121_1265, this->sr / (number)100, this->sr / (number)100);
            number add_1123_1268 = slide_1122_1267 + scale_1120_1264;
            number latch_1124_1270 = this->gen_01_latch_1269_next(add_1123_1268, eq_1089_1229);
            number slide_1126_1273 = this->gen_01_slide_1272_next(clamp_1125_1271, this->sr / (number)100, this->sr / (number)100);
            number mul_1127_1274 = noise_1109_1251 * slide_1126_1273;
            number pow_1128_1275 = fixnan(rnbo_pow(int_1077_1214, mul_1127_1274));
            number slide_1130_1279 = this->gen_01_slide_1278_next(clamp_1129_1276, this->sr / (number)100, this->sr / (number)100);
            number round_1131_1280 = rnbo_fround(slide_1130_1279 * 1 / (number)1) * 1;
            number div_1132_1281 = round_1131_1280 / (number)12;
            number pow_1133_1282 = fixnan(rnbo_pow(int_1076_1213, div_1132_1281));
            number mul_1134_1283 = pow_1133_1282 * pow_1128_1275;
            number latch_1135_1285 = this->gen_01_latch_1284_next(mul_1134_1283, eq_1089_1229);
            number mul_1136_1286 = min_1102_1243 * latch_1135_1285;
            number add_1137_1287 = mul_1136_1286 + latch_1124_1270;
            number sample_sample_1138 = 0;
            number index_sample_1139 = 0;
            auto result_1288 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1137_1287, 0);
            index_sample_1139 = result_1288[1];
            sample_sample_1138 = result_1288[0];
            number mul_1140_1289 = sample_sample_1138 * sub_1107_1248;
            number mul_1141_1290 = mul_1140_1289 * sqrt_1097_1238;
            number gen_1142_1291 = mul_1141_1290;
            number mul_1143_1292 = mul_1140_1289 * sqrt_1095_1236;
            number gen_1144_1293 = mul_1143_1292;
            number float_1149_1298 = float(0.5);
            number slide_1153_1303 = this->gen_01_slide_1302_next(clamp_1152_1301, this->sr / (number)100, this->sr / (number)100);
            number noise_1154_1305 = this->gen_01_noise_1304_next();
            number slide_1162_1314 = this->gen_01_slide_1313_next(clamp_1161_1312, this->sr / (number)100, this->sr / (number)100);
            number phasor_1163_1316 = this->gen_01_phasor_1315_next(slide_1162_1314, 0);
            number delta_1164_1318 = this->gen_01_delta_1317_next(phasor_1163_1316);
            number lt_1165_1319 = delta_1164_1318 < 0;
            number counter_1166 = 0;
            number counter_1167 = 0;
            number counter_1168 = 0;
            array<number, 3> result_1321 = this->gen_01_counter_1320_next(lt_1165_1319, Rst_1145_1294, int_1151_1300);
            counter_1168 = result_1321[2];
            counter_1167 = result_1321[1];
            counter_1166 = result_1321[0];
            number eq_1169_1322 = counter_1166 == clamp_1150_1299;
            number delta_1170_1324 = this->gen_01_delta_1323_next(eq_1169_1322);
            number eq_1171_1325 = delta_1170_1324 == 1;
            number gen_1172_1326 = eq_1171_1325;
            number latch_1173_1328 = this->gen_01_latch_1327_next(noise_1154_1305, eq_1171_1325);
            number mul_1174_1329 = latch_1173_1328 * 0.5;
            number mul_1175_1330 = mul_1174_1329 * slide_1153_1303;
            number add_1176_1331 = mul_1175_1330 + 0.5;
            number sqrt_1177_1332 = (add_1176_1331 <= 0 ? 0 : rnbo_sqrt(add_1176_1331));
            number rsub_1178_1333 = 1 - add_1176_1331;
            number sqrt_1179_1334 = (rsub_1178_1333 <= 0 ? 0 : rnbo_sqrt(rsub_1178_1333));
            number latch_1180_1336 = this->gen_01_latch_1335_next(mstosamps_1157_1308, eq_1171_1325);
            number counter_1181 = 0;
            number counter_1182 = 0;
            number counter_1183 = 0;
            array<number, 3> result_1338 = this->gen_01_counter_1337_next(int_1155_1306, eq_1171_1325, 0);
            counter_1183 = result_1338[2];
            counter_1182 = result_1338[1];
            counter_1181 = result_1338[0];
            auto min_1184_1339 = this->minimum(counter_1181, latch_1180_1336);
            number div_1185_1340 = (latch_1180_1336 == 0. ? 0. : min_1184_1339 / latch_1180_1336);
            number mul_1186_1341 = div_1185_1340 * 6.28318530717958647692;
            number cos_1187_1342 = rnbo_cos(mul_1186_1341);
            number mul_1188_1343 = cos_1187_1342 * 0.5;
            number sub_1189_1344 = float_1149_1298 - mul_1188_1343;
            number gen_1190_1345 = sub_1189_1344;
            number noise_1191_1347 = this->gen_01_noise_1346_next();
            number noise_1192_1349 = this->gen_01_noise_1348_next();
            number abs_1193_1350 = rnbo_abs(noise_1192_1349);
            number slide_1195_1353 = this->gen_01_slide_1352_next(clamp_1194_1351, this->sr / (number)100, this->sr / (number)100);
            number mul_1196_1354 = abs_1193_1350 * slide_1195_1353;
            auto scale_1202_1360 = this->scale(mul_1196_1354, 0, 1, 0, sub_1201_1359, 1);
            number slide_1204_1363 = this->gen_01_slide_1362_next(scale_1203_1361, this->sr / (number)100, this->sr / (number)100);
            number add_1205_1364 = slide_1204_1363 + scale_1202_1360;
            number latch_1206_1366 = this->gen_01_latch_1365_next(add_1205_1364, eq_1171_1325);
            number slide_1208_1370 = this->gen_01_slide_1369_next(clamp_1207_1367, this->sr / (number)100, this->sr / (number)100);
            number mul_1209_1371 = noise_1191_1347 * slide_1208_1370;
            number pow_1210_1372 = fixnan(rnbo_pow(int_1159_1310, mul_1209_1371));
            number slide_1212_1375 = this->gen_01_slide_1374_next(clamp_1211_1373, this->sr / (number)100, this->sr / (number)100);
            number round_1213_1376 = rnbo_fround(slide_1212_1375 * 1 / (number)1) * 1;
            number div_1214_1377 = round_1213_1376 / (number)12;
            number pow_1215_1378 = fixnan(rnbo_pow(int_1158_1309, div_1214_1377));
            number mul_1216_1379 = pow_1215_1378 * pow_1210_1372;
            number latch_1217_1381 = this->gen_01_latch_1380_next(mul_1216_1379, eq_1171_1325);
            number mul_1218_1382 = min_1184_1339 * latch_1217_1381;
            number add_1219_1383 = mul_1218_1382 + latch_1206_1366;
            number sample_sample_1220 = 0;
            number index_sample_1221 = 0;
            auto result_1384 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1219_1383, 0);
            index_sample_1221 = result_1384[1];
            sample_sample_1220 = result_1384[0];
            number mul_1222_1385 = sample_sample_1220 * sub_1189_1344;
            number mul_1223_1386 = mul_1222_1385 * sqrt_1177_1332;
            number gen_1224_1387 = mul_1223_1386;
            number mul_1225_1388 = mul_1222_1385 * sqrt_1179_1334;
            number gen_1226_1389 = mul_1225_1388;
            number float_1231_1394 = float(0.5);
            number slide_1235_1399 = this->gen_01_slide_1398_next(clamp_1234_1397, this->sr / (number)100, this->sr / (number)100);
            number noise_1236_1402 = this->gen_01_noise_1401_next();
            number slide_1244_1411 = this->gen_01_slide_1410_next(clamp_1243_1409, this->sr / (number)100, this->sr / (number)100);
            number phasor_1245_1413 = this->gen_01_phasor_1412_next(slide_1244_1411, 0);
            number delta_1246_1415 = this->gen_01_delta_1414_next(phasor_1245_1413);
            number lt_1247_1416 = delta_1246_1415 < 0;
            number counter_1248 = 0;
            number counter_1249 = 0;
            number counter_1250 = 0;
            array<number, 3> result_1418 = this->gen_01_counter_1417_next(lt_1247_1416, Rst_1227_1390, int_1233_1396);
            counter_1250 = result_1418[2];
            counter_1249 = result_1418[1];
            counter_1248 = result_1418[0];
            number eq_1251_1419 = counter_1248 == clamp_1232_1395;
            number delta_1252_1421 = this->gen_01_delta_1420_next(eq_1251_1419);
            number eq_1253_1422 = delta_1252_1421 == 1;
            number gen_1254_1423 = eq_1253_1422;
            number latch_1255_1425 = this->gen_01_latch_1424_next(noise_1236_1402, eq_1253_1422);
            number mul_1256_1426 = latch_1255_1425 * 0.5;
            number mul_1257_1427 = mul_1256_1426 * slide_1235_1399;
            number add_1258_1428 = mul_1257_1427 + 0.5;
            number sqrt_1259_1429 = (add_1258_1428 <= 0 ? 0 : rnbo_sqrt(add_1258_1428));
            number rsub_1260_1430 = 1 - add_1258_1428;
            number sqrt_1261_1431 = (rsub_1260_1430 <= 0 ? 0 : rnbo_sqrt(rsub_1260_1430));
            number latch_1262_1433 = this->gen_01_latch_1432_next(mstosamps_1239_1405, eq_1253_1422);
            number counter_1263 = 0;
            number counter_1264 = 0;
            number counter_1265 = 0;
            array<number, 3> result_1435 = this->gen_01_counter_1434_next(int_1237_1403, eq_1253_1422, 0);
            counter_1265 = result_1435[2];
            counter_1264 = result_1435[1];
            counter_1263 = result_1435[0];
            auto min_1266_1436 = this->minimum(counter_1263, latch_1262_1433);
            number div_1267_1437 = (latch_1262_1433 == 0. ? 0. : min_1266_1436 / latch_1262_1433);
            number mul_1268_1438 = div_1267_1437 * 6.28318530717958647692;
            number cos_1269_1439 = rnbo_cos(mul_1268_1438);
            number mul_1270_1440 = cos_1269_1439 * 0.5;
            number sub_1271_1441 = float_1231_1394 - mul_1270_1440;
            number gen_1272_1442 = sub_1271_1441;
            number noise_1273_1444 = this->gen_01_noise_1443_next();
            number noise_1274_1446 = this->gen_01_noise_1445_next();
            number abs_1275_1447 = rnbo_abs(noise_1274_1446);
            number slide_1277_1450 = this->gen_01_slide_1449_next(clamp_1276_1448, this->sr / (number)100, this->sr / (number)100);
            number mul_1278_1451 = abs_1275_1447 * slide_1277_1450;
            auto scale_1284_1457 = this->scale(mul_1278_1451, 0, 1, 0, sub_1283_1456, 1);
            number slide_1286_1460 = this->gen_01_slide_1459_next(scale_1285_1458, this->sr / (number)100, this->sr / (number)100);
            number add_1287_1461 = slide_1286_1460 + scale_1284_1457;
            number latch_1288_1463 = this->gen_01_latch_1462_next(add_1287_1461, eq_1253_1422);
            number slide_1290_1466 = this->gen_01_slide_1465_next(clamp_1289_1464, this->sr / (number)100, this->sr / (number)100);
            number mul_1291_1467 = noise_1273_1444 * slide_1290_1466;
            number pow_1292_1468 = fixnan(rnbo_pow(int_1241_1407, mul_1291_1467));
            number slide_1294_1471 = this->gen_01_slide_1470_next(clamp_1293_1469, this->sr / (number)100, this->sr / (number)100);
            number round_1295_1472 = rnbo_fround(slide_1294_1471 * 1 / (number)1) * 1;
            number div_1296_1473 = round_1295_1472 / (number)12;
            number pow_1297_1474 = fixnan(rnbo_pow(int_1240_1406, div_1296_1473));
            number mul_1298_1475 = pow_1297_1474 * pow_1292_1468;
            number latch_1299_1477 = this->gen_01_latch_1476_next(mul_1298_1475, eq_1253_1422);
            number mul_1300_1478 = min_1266_1436 * latch_1299_1477;
            number add_1301_1479 = mul_1300_1478 + latch_1288_1463;
            number sample_sample_1302 = 0;
            number index_sample_1303 = 0;
            auto result_1480 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1301_1479, 0);
            index_sample_1303 = result_1480[1];
            sample_sample_1302 = result_1480[0];
            number mul_1304_1481 = sample_sample_1302 * sub_1271_1441;
            number mul_1305_1482 = mul_1304_1481 * sqrt_1259_1429;
            number gen_1306_1483 = mul_1305_1482;
            number mul_1307_1484 = mul_1304_1481 * sqrt_1261_1431;
            number gen_1308_1485 = mul_1307_1484;
            number float_1313_1490 = float(0.5);
            number slide_1317_1495 = this->gen_01_slide_1494_next(clamp_1316_1493, this->sr / (number)100, this->sr / (number)100);
            number noise_1318_1497 = this->gen_01_noise_1496_next();
            number slide_1326_1506 = this->gen_01_slide_1505_next(clamp_1325_1504, this->sr / (number)100, this->sr / (number)100);
            number phasor_1327_1508 = this->gen_01_phasor_1507_next(slide_1326_1506, 0);
            number delta_1328_1510 = this->gen_01_delta_1509_next(phasor_1327_1508);
            number lt_1329_1511 = delta_1328_1510 < 0;
            number counter_1330 = 0;
            number counter_1331 = 0;
            number counter_1332 = 0;
            array<number, 3> result_1513 = this->gen_01_counter_1512_next(lt_1329_1511, Rst_1309_1486, int_1315_1492);
            counter_1332 = result_1513[2];
            counter_1331 = result_1513[1];
            counter_1330 = result_1513[0];
            number eq_1333_1514 = counter_1330 == clamp_1314_1491;
            number delta_1334_1516 = this->gen_01_delta_1515_next(eq_1333_1514);
            number eq_1335_1517 = delta_1334_1516 == 1;
            number gen_1336_1518 = eq_1335_1517;
            number latch_1337_1520 = this->gen_01_latch_1519_next(noise_1318_1497, eq_1335_1517);
            number mul_1338_1521 = latch_1337_1520 * 0.5;
            number mul_1339_1522 = mul_1338_1521 * slide_1317_1495;
            number add_1340_1523 = mul_1339_1522 + 0.5;
            number sqrt_1341_1524 = (add_1340_1523 <= 0 ? 0 : rnbo_sqrt(add_1340_1523));
            number rsub_1342_1525 = 1 - add_1340_1523;
            number sqrt_1343_1526 = (rsub_1342_1525 <= 0 ? 0 : rnbo_sqrt(rsub_1342_1525));
            number latch_1344_1528 = this->gen_01_latch_1527_next(mstosamps_1321_1500, eq_1335_1517);
            number counter_1345 = 0;
            number counter_1346 = 0;
            number counter_1347 = 0;
            array<number, 3> result_1530 = this->gen_01_counter_1529_next(int_1319_1498, eq_1335_1517, 0);
            counter_1347 = result_1530[2];
            counter_1346 = result_1530[1];
            counter_1345 = result_1530[0];
            auto min_1348_1531 = this->minimum(counter_1345, latch_1344_1528);
            number div_1349_1532 = (latch_1344_1528 == 0. ? 0. : min_1348_1531 / latch_1344_1528);
            number mul_1350_1533 = div_1349_1532 * 6.28318530717958647692;
            number cos_1351_1534 = rnbo_cos(mul_1350_1533);
            number mul_1352_1535 = cos_1351_1534 * 0.5;
            number sub_1353_1536 = float_1313_1490 - mul_1352_1535;
            number gen_1354_1537 = sub_1353_1536;
            number noise_1355_1539 = this->gen_01_noise_1538_next();
            number noise_1356_1541 = this->gen_01_noise_1540_next();
            number abs_1357_1542 = rnbo_abs(noise_1356_1541);
            number slide_1359_1545 = this->gen_01_slide_1544_next(clamp_1358_1543, this->sr / (number)100, this->sr / (number)100);
            number mul_1360_1546 = abs_1357_1542 * slide_1359_1545;
            auto scale_1366_1552 = this->scale(mul_1360_1546, 0, 1, 0, sub_1365_1551, 1);
            number slide_1368_1555 = this->gen_01_slide_1554_next(scale_1367_1553, this->sr / (number)100, this->sr / (number)100);
            number add_1369_1556 = slide_1368_1555 + scale_1366_1552;
            number latch_1370_1558 = this->gen_01_latch_1557_next(add_1369_1556, eq_1335_1517);
            number slide_1372_1561 = this->gen_01_slide_1560_next(clamp_1371_1559, this->sr / (number)100, this->sr / (number)100);
            number mul_1373_1562 = noise_1355_1539 * slide_1372_1561;
            number pow_1374_1563 = fixnan(rnbo_pow(int_1323_1502, mul_1373_1562));
            number slide_1376_1566 = this->gen_01_slide_1565_next(clamp_1375_1564, this->sr / (number)100, this->sr / (number)100);
            number round_1377_1567 = rnbo_fround(slide_1376_1566 * 1 / (number)1) * 1;
            number div_1378_1568 = round_1377_1567 / (number)12;
            number pow_1379_1569 = fixnan(rnbo_pow(int_1322_1501, div_1378_1568));
            number mul_1380_1570 = pow_1379_1569 * pow_1374_1563;
            number latch_1381_1572 = this->gen_01_latch_1571_next(mul_1380_1570, eq_1335_1517);
            number mul_1382_1573 = min_1348_1531 * latch_1381_1572;
            number add_1383_1574 = mul_1382_1573 + latch_1370_1558;
            number sample_sample_1384 = 0;
            number index_sample_1385 = 0;
            auto result_1575 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1383_1574, 0);
            index_sample_1385 = result_1575[1];
            sample_sample_1384 = result_1575[0];
            number mul_1386_1576 = sample_sample_1384 * sub_1353_1536;
            number mul_1387_1577 = mul_1386_1576 * sqrt_1341_1524;
            number gen_1388_1578 = mul_1387_1577;
            number mul_1389_1579 = mul_1386_1576 * sqrt_1343_1526;
            number gen_1390_1580 = mul_1389_1579;
            number float_1395_1585 = float(0.5);
            number slide_1399_1590 = this->gen_01_slide_1589_next(clamp_1398_1588, this->sr / (number)100, this->sr / (number)100);
            number noise_1400_1592 = this->gen_01_noise_1591_next();
            number slide_1405_1598 = this->gen_01_slide_1597_next(clamp_1404_1596, this->sr / (number)100, this->sr / (number)100);
            number phasor_1406_1600 = this->gen_01_phasor_1599_next(slide_1405_1598, 0);
            number delta_1407_1602 = this->gen_01_delta_1601_next(phasor_1406_1600);
            number lt_1408_1603 = delta_1407_1602 < 0;
            number counter_1409 = 0;
            number counter_1410 = 0;
            number counter_1411 = 0;
            array<number, 3> result_1605 = this->gen_01_counter_1604_next(lt_1408_1603, Rst_1391_1581, int_1397_1587);
            counter_1411 = result_1605[2];
            counter_1410 = result_1605[1];
            counter_1409 = result_1605[0];
            number eq_1412_1606 = counter_1409 == clamp_1396_1586;
            number delta_1413_1608 = this->gen_01_delta_1607_next(eq_1412_1606);
            number eq_1414_1609 = delta_1413_1608 == 1;
            number gen_1415_1610 = eq_1414_1609;
            number latch_1416_1612 = this->gen_01_latch_1611_next(noise_1400_1592, eq_1414_1609);
            number mul_1417_1613 = latch_1416_1612 * 0.5;
            number mul_1418_1614 = mul_1417_1613 * slide_1399_1590;
            number add_1419_1615 = mul_1418_1614 + 0.5;
            number sqrt_1420_1616 = (add_1419_1615 <= 0 ? 0 : rnbo_sqrt(add_1419_1615));
            number rsub_1421_1617 = 1 - add_1419_1615;
            number sqrt_1422_1618 = (rsub_1421_1617 <= 0 ? 0 : rnbo_sqrt(rsub_1421_1617));
            number latch_1423_1620 = this->gen_01_latch_1619_next(mstosamps_1403_1595, eq_1414_1609);
            number counter_1424 = 0;
            number counter_1425 = 0;
            number counter_1426 = 0;
            array<number, 3> result_1622 = this->gen_01_counter_1621_next(int_1401_1593, eq_1414_1609, 0);
            counter_1426 = result_1622[2];
            counter_1425 = result_1622[1];
            counter_1424 = result_1622[0];
            auto min_1427_1623 = this->minimum(counter_1424, latch_1423_1620);
            number div_1428_1624 = (latch_1423_1620 == 0. ? 0. : min_1427_1623 / latch_1423_1620);
            number mul_1429_1625 = div_1428_1624 * 6.28318530717958647692;
            number cos_1430_1626 = rnbo_cos(mul_1429_1625);
            number mul_1431_1627 = cos_1430_1626 * 0.5;
            number sub_1432_1628 = float_1395_1585 - mul_1431_1627;
            number gen_1433_1629 = sub_1432_1628;
            number noise_1437_1634 = this->gen_01_noise_1633_next();
            number noise_1438_1636 = this->gen_01_noise_1635_next();
            number abs_1439_1637 = rnbo_abs(noise_1438_1636);
            number slide_1441_1640 = this->gen_01_slide_1639_next(clamp_1440_1638, this->sr / (number)100, this->sr / (number)100);
            number mul_1442_1641 = abs_1439_1637 * slide_1441_1640;
            auto scale_1448_1647 = this->scale(mul_1442_1641, 0, 1, 0, sub_1447_1646, 1);
            number slide_1450_1650 = this->gen_01_slide_1649_next(scale_1449_1648, this->sr / (number)100, this->sr / (number)100);
            number add_1451_1651 = slide_1450_1650 + scale_1448_1647;
            number latch_1452_1653 = this->gen_01_latch_1652_next(add_1451_1651, eq_1414_1609);
            number slide_1454_1656 = this->gen_01_slide_1655_next(clamp_1453_1654, this->sr / (number)100, this->sr / (number)100);
            number mul_1455_1657 = noise_1437_1634 * slide_1454_1656;
            number pow_1456_1658 = fixnan(rnbo_pow(int_1435_1631, mul_1455_1657));
            number slide_1458_1661 = this->gen_01_slide_1660_next(clamp_1457_1659, this->sr / (number)100, this->sr / (number)100);
            number round_1459_1662 = rnbo_fround(slide_1458_1661 * 1 / (number)1) * 1;
            number div_1460_1663 = round_1459_1662 / (number)12;
            number pow_1461_1664 = fixnan(rnbo_pow(int_1434_1630, div_1460_1663));
            number mul_1462_1665 = pow_1461_1664 * pow_1456_1658;
            number latch_1463_1668 = this->gen_01_latch_1667_next(mul_1462_1665, eq_1414_1609);
            number mul_1464_1669 = min_1427_1623 * latch_1463_1668;
            number add_1465_1670 = mul_1464_1669 + latch_1452_1653;
            number sample_sample_1466 = 0;
            number index_sample_1467 = 0;
            auto result_1671 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1465_1670, 0);
            index_sample_1467 = result_1671[1];
            sample_sample_1466 = result_1671[0];
            number mul_1468_1672 = sample_sample_1466 * sub_1432_1628;
            number mul_1469_1673 = mul_1468_1672 * sqrt_1422_1618;
            number gen_1470_1674 = mul_1469_1673;
            number mul_1471_1675 = mul_1468_1672 * sqrt_1420_1616;
            number gen_1472_1676 = mul_1471_1675;
            number float_1477_1681 = float(0.5);
            number slide_1481_1686 = this->gen_01_slide_1685_next(clamp_1480_1684, this->sr / (number)100, this->sr / (number)100);
            number noise_1482_1688 = this->gen_01_noise_1687_next();
            number slide_1487_1694 = this->gen_01_slide_1693_next(clamp_1486_1692, this->sr / (number)100, this->sr / (number)100);
            number phasor_1488_1696 = this->gen_01_phasor_1695_next(slide_1487_1694, 0);
            number delta_1489_1698 = this->gen_01_delta_1697_next(phasor_1488_1696);
            number lt_1490_1699 = delta_1489_1698 < 0;
            number counter_1491 = 0;
            number counter_1492 = 0;
            number counter_1493 = 0;
            array<number, 3> result_1701 = this->gen_01_counter_1700_next(lt_1490_1699, Rst_1473_1677, int_1479_1683);
            counter_1493 = result_1701[2];
            counter_1492 = result_1701[1];
            counter_1491 = result_1701[0];
            number eq_1494_1702 = counter_1491 == clamp_1478_1682;
            number delta_1495_1704 = this->gen_01_delta_1703_next(eq_1494_1702);
            number eq_1496_1705 = delta_1495_1704 == 1;
            number gen_1497_1706 = eq_1496_1705;
            number latch_1498_1708 = this->gen_01_latch_1707_next(mstosamps_1485_1691, eq_1496_1705);
            number latch_1499_1711 = this->gen_01_latch_1710_next(noise_1482_1688, eq_1496_1705);
            number mul_1500_1712 = latch_1499_1711 * 0.5;
            number mul_1501_1713 = mul_1500_1712 * slide_1481_1686;
            number add_1502_1714 = mul_1501_1713 + 0.5;
            number sqrt_1503_1715 = (add_1502_1714 <= 0 ? 0 : rnbo_sqrt(add_1502_1714));
            number rsub_1504_1716 = 1 - add_1502_1714;
            number sqrt_1505_1717 = (rsub_1504_1716 <= 0 ? 0 : rnbo_sqrt(rsub_1504_1716));
            number counter_1506 = 0;
            number counter_1507 = 0;
            number counter_1508 = 0;
            array<number, 3> result_1719 = this->gen_01_counter_1718_next(int_1483_1689, eq_1496_1705, 0);
            counter_1508 = result_1719[2];
            counter_1507 = result_1719[1];
            counter_1506 = result_1719[0];
            auto min_1509_1720 = this->minimum(counter_1506, latch_1498_1708);
            number div_1510_1721 = (latch_1498_1708 == 0. ? 0. : min_1509_1720 / latch_1498_1708);
            number mul_1511_1722 = div_1510_1721 * 6.28318530717958647692;
            number cos_1512_1723 = rnbo_cos(mul_1511_1722);
            number mul_1513_1724 = cos_1512_1723 * 0.5;
            number sub_1514_1725 = float_1477_1681 - mul_1513_1724;
            number gen_1515_1726 = sub_1514_1725;
            number noise_1519_1731 = this->gen_01_noise_1730_next();
            number noise_1520_1733 = this->gen_01_noise_1732_next();
            number abs_1521_1734 = rnbo_abs(noise_1520_1733);
            number slide_1523_1737 = this->gen_01_slide_1736_next(clamp_1522_1735, this->sr / (number)100, this->sr / (number)100);
            number mul_1524_1738 = abs_1521_1734 * slide_1523_1737;
            auto scale_1530_1744 = this->scale(mul_1524_1738, 0, 1, 0, sub_1529_1743, 1);
            number slide_1532_1747 = this->gen_01_slide_1746_next(scale_1531_1745, this->sr / (number)100, this->sr / (number)100);
            number add_1533_1748 = slide_1532_1747 + scale_1530_1744;
            number latch_1534_1750 = this->gen_01_latch_1749_next(add_1533_1748, eq_1496_1705);
            number slide_1536_1753 = this->gen_01_slide_1752_next(clamp_1535_1751, this->sr / (number)100, this->sr / (number)100);
            number mul_1537_1754 = noise_1519_1731 * slide_1536_1753;
            number pow_1538_1755 = fixnan(rnbo_pow(int_1517_1728, mul_1537_1754));
            number slide_1540_1758 = this->gen_01_slide_1757_next(clamp_1539_1756, this->sr / (number)100, this->sr / (number)100);
            number round_1541_1759 = rnbo_fround(slide_1540_1758 * 1 / (number)1) * 1;
            number div_1542_1760 = round_1541_1759 / (number)12;
            number pow_1543_1761 = fixnan(rnbo_pow(int_1516_1727, div_1542_1760));
            number mul_1544_1762 = pow_1543_1761 * pow_1538_1755;
            number latch_1545_1764 = this->gen_01_latch_1763_next(mul_1544_1762, eq_1496_1705);
            number mul_1546_1765 = min_1509_1720 * latch_1545_1764;
            number add_1547_1766 = mul_1546_1765 + latch_1534_1750;
            number sample_sample_1548 = 0;
            number index_sample_1549 = 0;
            auto result_1767 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1547_1766, 0);
            index_sample_1549 = result_1767[1];
            sample_sample_1548 = result_1767[0];
            number mul_1550_1768 = sample_sample_1548 * sub_1514_1725;
            number mul_1551_1769 = mul_1550_1768 * sqrt_1505_1717;
            number gen_1552_1770 = mul_1551_1769;
            number mul_1553_1771 = mul_1550_1768 * sqrt_1503_1715;
            number gen_1554_1772 = mul_1553_1771;
            number float_1559_1777 = float(0.5);
            number slide_1563_1782 = this->gen_01_slide_1781_next(clamp_1562_1780, this->sr / (number)100, this->sr / (number)100);
            number noise_1564_1784 = this->gen_01_noise_1783_next();
            number slide_1572_1793 = this->gen_01_slide_1792_next(clamp_1571_1791, this->sr / (number)100, this->sr / (number)100);
            number phasor_1573_1795 = this->gen_01_phasor_1794_next(slide_1572_1793, 0);
            number delta_1574_1797 = this->gen_01_delta_1796_next(phasor_1573_1795);
            number lt_1575_1798 = delta_1574_1797 < 0;
            number counter_1576 = 0;
            number counter_1577 = 0;
            number counter_1578 = 0;
            array<number, 3> result_1800 = this->gen_01_counter_1799_next(lt_1575_1798, Rst_1555_1773, int_1561_1779);
            counter_1578 = result_1800[2];
            counter_1577 = result_1800[1];
            counter_1576 = result_1800[0];
            number eq_1579_1801 = counter_1576 == clamp_1560_1778;
            number delta_1580_1803 = this->gen_01_delta_1802_next(eq_1579_1801);
            number eq_1581_1804 = delta_1580_1803 == 1;
            number gen_1582_1805 = eq_1581_1804;
            number latch_1583_1807 = this->gen_01_latch_1806_next(mstosamps_1567_1787, eq_1581_1804);
            number latch_1584_1809 = this->gen_01_latch_1808_next(noise_1564_1784, eq_1581_1804);
            number mul_1585_1810 = latch_1584_1809 * 0.5;
            number mul_1586_1811 = mul_1585_1810 * slide_1563_1782;
            number add_1587_1812 = mul_1586_1811 + 0.5;
            number sqrt_1588_1813 = (add_1587_1812 <= 0 ? 0 : rnbo_sqrt(add_1587_1812));
            number rsub_1589_1814 = 1 - add_1587_1812;
            number sqrt_1590_1815 = (rsub_1589_1814 <= 0 ? 0 : rnbo_sqrt(rsub_1589_1814));
            number counter_1591 = 0;
            number counter_1592 = 0;
            number counter_1593 = 0;
            array<number, 3> result_1817 = this->gen_01_counter_1816_next(int_1565_1785, eq_1581_1804, 0);
            counter_1593 = result_1817[2];
            counter_1592 = result_1817[1];
            counter_1591 = result_1817[0];
            auto min_1594_1818 = this->minimum(counter_1591, latch_1583_1807);
            number div_1595_1819 = (latch_1583_1807 == 0. ? 0. : min_1594_1818 / latch_1583_1807);
            number mul_1596_1820 = div_1595_1819 * 6.28318530717958647692;
            number cos_1597_1821 = rnbo_cos(mul_1596_1820);
            number mul_1598_1822 = cos_1597_1821 * 0.5;
            number sub_1599_1823 = float_1559_1777 - mul_1598_1822;
            number gen_1600_1824 = sub_1599_1823;
            number noise_1601_1826 = this->gen_01_noise_1825_next();
            number noise_1602_1828 = this->gen_01_noise_1827_next();
            number abs_1603_1829 = rnbo_abs(noise_1602_1828);
            number slide_1605_1832 = this->gen_01_slide_1831_next(clamp_1604_1830, this->sr / (number)100, this->sr / (number)100);
            number mul_1606_1833 = abs_1603_1829 * slide_1605_1832;
            auto scale_1612_1839 = this->scale(mul_1606_1833, 0, 1, 0, sub_1611_1838, 1);
            number slide_1614_1842 = this->gen_01_slide_1841_next(scale_1613_1840, this->sr / (number)100, this->sr / (number)100);
            number add_1615_1843 = slide_1614_1842 + scale_1612_1839;
            number latch_1616_1845 = this->gen_01_latch_1844_next(add_1615_1843, eq_1581_1804);
            number slide_1618_1848 = this->gen_01_slide_1847_next(clamp_1617_1846, this->sr / (number)100, this->sr / (number)100);
            number mul_1619_1849 = noise_1601_1826 * slide_1618_1848;
            number pow_1620_1850 = fixnan(rnbo_pow(int_1569_1789, mul_1619_1849));
            number slide_1622_1853 = this->gen_01_slide_1852_next(clamp_1621_1851, this->sr / (number)100, this->sr / (number)100);
            number round_1623_1854 = rnbo_fround(slide_1622_1853 * 1 / (number)1) * 1;
            number div_1624_1855 = round_1623_1854 / (number)12;
            number pow_1625_1856 = fixnan(rnbo_pow(int_1568_1788, div_1624_1855));
            number mul_1626_1857 = pow_1625_1856 * pow_1620_1850;
            number latch_1627_1859 = this->gen_01_latch_1858_next(mul_1626_1857, eq_1581_1804);
            number mul_1628_1860 = min_1594_1818 * latch_1627_1859;
            number add_1629_1861 = mul_1628_1860 + latch_1616_1845;
            number sample_sample_1630 = 0;
            number index_sample_1631 = 0;
            auto result_1862 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1629_1861, 0);
            index_sample_1631 = result_1862[1];
            sample_sample_1630 = result_1862[0];
            number mul_1632_1863 = sample_sample_1630 * sub_1599_1823;
            number mul_1633_1864 = mul_1632_1863 * sqrt_1590_1815;
            number gen_1634_1865 = mul_1633_1864;
            number mul_1635_1866 = mul_1632_1863 * sqrt_1588_1813;
            number gen_1636_1867 = mul_1635_1866;
            number float_1641_1872 = float(0.5);
            number slide_1645_1877 = this->gen_01_slide_1876_next(clamp_1644_1875, this->sr / (number)100, this->sr / (number)100);
            number noise_1646_1879 = this->gen_01_noise_1878_next();
            number slide_1654_1888 = this->gen_01_slide_1887_next(clamp_1653_1886, this->sr / (number)100, this->sr / (number)100);
            number phasor_1655_1890 = this->gen_01_phasor_1889_next(slide_1654_1888, 0);
            number delta_1656_1892 = this->gen_01_delta_1891_next(phasor_1655_1890);
            number lt_1657_1893 = delta_1656_1892 < 0;
            number counter_1658 = 0;
            number counter_1659 = 0;
            number counter_1660 = 0;
            array<number, 3> result_1895 = this->gen_01_counter_1894_next(lt_1657_1893, Rst_1637_1868, int_1643_1874);
            counter_1660 = result_1895[2];
            counter_1659 = result_1895[1];
            counter_1658 = result_1895[0];
            number eq_1661_1896 = counter_1658 == clamp_1642_1873;
            number delta_1662_1898 = this->gen_01_delta_1897_next(eq_1661_1896);
            number eq_1663_1899 = delta_1662_1898 == 1;
            number gen_1664_1900 = eq_1663_1899;
            number latch_1665_1902 = this->gen_01_latch_1901_next(mstosamps_1649_1882, eq_1663_1899);
            number latch_1666_1904 = this->gen_01_latch_1903_next(noise_1646_1879, eq_1663_1899);
            number mul_1667_1905 = latch_1666_1904 * 0.5;
            number mul_1668_1906 = mul_1667_1905 * slide_1645_1877;
            number add_1669_1907 = mul_1668_1906 + 0.5;
            number sqrt_1670_1908 = (add_1669_1907 <= 0 ? 0 : rnbo_sqrt(add_1669_1907));
            number rsub_1671_1909 = 1 - add_1669_1907;
            number sqrt_1672_1910 = (rsub_1671_1909 <= 0 ? 0 : rnbo_sqrt(rsub_1671_1909));
            number counter_1673 = 0;
            number counter_1674 = 0;
            number counter_1675 = 0;
            array<number, 3> result_1912 = this->gen_01_counter_1911_next(int_1647_1880, eq_1663_1899, 0);
            counter_1675 = result_1912[2];
            counter_1674 = result_1912[1];
            counter_1673 = result_1912[0];
            auto min_1676_1913 = this->minimum(counter_1673, latch_1665_1902);
            number div_1677_1914 = (latch_1665_1902 == 0. ? 0. : min_1676_1913 / latch_1665_1902);
            number mul_1678_1915 = div_1677_1914 * 6.28318530717958647692;
            number cos_1679_1916 = rnbo_cos(mul_1678_1915);
            number mul_1680_1917 = cos_1679_1916 * 0.5;
            number sub_1681_1918 = float_1641_1872 - mul_1680_1917;
            number gen_1682_1919 = sub_1681_1918;
            number noise_1683_1921 = this->gen_01_noise_1920_next();
            number noise_1684_1923 = this->gen_01_noise_1922_next();
            number abs_1685_1924 = rnbo_abs(noise_1684_1923);
            number slide_1687_1927 = this->gen_01_slide_1926_next(clamp_1686_1925, this->sr / (number)100, this->sr / (number)100);
            number mul_1688_1928 = abs_1685_1924 * slide_1687_1927;
            auto scale_1694_1934 = this->scale(mul_1688_1928, 0, 1, 0, sub_1693_1933, 1);
            number slide_1696_1937 = this->gen_01_slide_1936_next(scale_1695_1935, this->sr / (number)100, this->sr / (number)100);
            number add_1697_1938 = slide_1696_1937 + scale_1694_1934;
            number latch_1698_1940 = this->gen_01_latch_1939_next(add_1697_1938, eq_1663_1899);
            number slide_1700_1944 = this->gen_01_slide_1943_next(clamp_1699_1941, this->sr / (number)100, this->sr / (number)100);
            number mul_1701_1945 = noise_1683_1921 * slide_1700_1944;
            number pow_1702_1946 = fixnan(rnbo_pow(int_1651_1884, mul_1701_1945));
            number slide_1704_1949 = this->gen_01_slide_1948_next(clamp_1703_1947, this->sr / (number)100, this->sr / (number)100);
            number round_1705_1950 = rnbo_fround(slide_1704_1949 * 1 / (number)1) * 1;
            number div_1706_1951 = round_1705_1950 / (number)12;
            number pow_1707_1952 = fixnan(rnbo_pow(int_1650_1883, div_1706_1951));
            number mul_1708_1953 = pow_1707_1952 * pow_1702_1946;
            number latch_1709_1955 = this->gen_01_latch_1954_next(mul_1708_1953, eq_1663_1899);
            number mul_1710_1956 = min_1676_1913 * latch_1709_1955;
            number add_1711_1957 = mul_1710_1956 + latch_1698_1940;
            number sample_sample_1712 = 0;
            number index_sample_1713 = 0;
            auto result_1958 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1711_1957, 0);
            index_sample_1713 = result_1958[1];
            sample_sample_1712 = result_1958[0];
            number mul_1714_1959 = sample_sample_1712 * sub_1681_1918;
            number mul_1715_1960 = mul_1714_1959 * sqrt_1672_1910;
            number gen_1716_1961 = mul_1715_1960;
            number mul_1717_1962 = mul_1714_1959 * sqrt_1670_1908;
            number gen_1718_1963 = mul_1717_1962;
            number float_1723_1968 = float(0.5);
            number slide_1727_1973 = this->gen_01_slide_1972_next(clamp_1726_1971, this->sr / (number)100, this->sr / (number)100);
            number noise_1728_1976 = this->gen_01_noise_1975_next();
            number slide_1733_1982 = this->gen_01_slide_1981_next(clamp_1732_1980, this->sr / (number)100, this->sr / (number)100);
            number phasor_1734_1985 = this->gen_01_phasor_1984_next(slide_1733_1982, 0);
            number delta_1735_1987 = this->gen_01_delta_1986_next(phasor_1734_1985);
            number lt_1736_1988 = delta_1735_1987 < 0;
            number counter_1737 = 0;
            number counter_1738 = 0;
            number counter_1739 = 0;
            array<number, 3> result_1990 = this->gen_01_counter_1989_next(lt_1736_1988, Rst_1719_1964, int_1725_1970);
            counter_1739 = result_1990[2];
            counter_1738 = result_1990[1];
            counter_1737 = result_1990[0];
            number eq_1740_1991 = counter_1737 == clamp_1724_1969;
            number delta_1741_1993 = this->gen_01_delta_1992_next(eq_1740_1991);
            number eq_1742_1994 = delta_1741_1993 == 1;
            number gen_1743_1995 = eq_1742_1994;
            number latch_1744_1997 = this->gen_01_latch_1996_next(mstosamps_1731_1979, eq_1742_1994);
            number latch_1745_1999 = this->gen_01_latch_1998_next(noise_1728_1976, eq_1742_1994);
            number mul_1746_2000 = latch_1745_1999 * 0.5;
            number mul_1747_2001 = mul_1746_2000 * slide_1727_1973;
            number add_1748_2002 = mul_1747_2001 + 0.5;
            number sqrt_1749_2003 = (add_1748_2002 <= 0 ? 0 : rnbo_sqrt(add_1748_2002));
            number rsub_1750_2004 = 1 - add_1748_2002;
            number sqrt_1751_2005 = (rsub_1750_2004 <= 0 ? 0 : rnbo_sqrt(rsub_1750_2004));
            number counter_1752 = 0;
            number counter_1753 = 0;
            number counter_1754 = 0;
            array<number, 3> result_2007 = this->gen_01_counter_2006_next(int_1729_1977, eq_1742_1994, 0);
            counter_1754 = result_2007[2];
            counter_1753 = result_2007[1];
            counter_1752 = result_2007[0];
            auto min_1755_2008 = this->minimum(counter_1752, latch_1744_1997);
            number div_1756_2009 = (latch_1744_1997 == 0. ? 0. : min_1755_2008 / latch_1744_1997);
            number mul_1757_2010 = div_1756_2009 * 6.28318530717958647692;
            number cos_1758_2011 = rnbo_cos(mul_1757_2010);
            number mul_1759_2012 = cos_1758_2011 * 0.5;
            number sub_1760_2013 = float_1723_1968 - mul_1759_2012;
            number gen_1761_2014 = sub_1760_2013;
            number noise_1765_2019 = this->gen_01_noise_2018_next();
            number noise_1766_2021 = this->gen_01_noise_2020_next();
            number abs_1767_2022 = rnbo_abs(noise_1766_2021);
            number slide_1769_2026 = this->gen_01_slide_2025_next(clamp_1768_2023, this->sr / (number)100, this->sr / (number)100);
            number mul_1770_2027 = abs_1767_2022 * slide_1769_2026;
            auto scale_1776_2033 = this->scale(mul_1770_2027, 0, 1, 0, sub_1775_2032, 1);
            number slide_1778_2036 = this->gen_01_slide_2035_next(scale_1777_2034, this->sr / (number)100, this->sr / (number)100);
            number add_1779_2037 = slide_1778_2036 + scale_1776_2033;
            number latch_1780_2039 = this->gen_01_latch_2038_next(add_1779_2037, eq_1742_1994);
            number slide_1782_2042 = this->gen_01_slide_2041_next(clamp_1781_2040, this->sr / (number)100, this->sr / (number)100);
            number mul_1783_2043 = noise_1765_2019 * slide_1782_2042;
            number pow_1784_2044 = fixnan(rnbo_pow(int_1763_2016, mul_1783_2043));
            number slide_1786_2047 = this->gen_01_slide_2046_next(clamp_1785_2045, this->sr / (number)100, this->sr / (number)100);
            number round_1787_2048 = rnbo_fround(slide_1786_2047 * 1 / (number)1) * 1;
            number div_1788_2049 = round_1787_2048 / (number)12;
            number pow_1789_2050 = fixnan(rnbo_pow(int_1762_2015, div_1788_2049));
            number mul_1790_2051 = pow_1789_2050 * pow_1784_2044;
            number latch_1791_2053 = this->gen_01_latch_2052_next(mul_1790_2051, eq_1742_1994);
            number mul_1792_2054 = min_1755_2008 * latch_1791_2053;
            number add_1793_2055 = mul_1792_2054 + latch_1780_2039;
            number sample_sample_1794 = 0;
            number index_sample_1795 = 0;
            auto result_2056 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1793_2055, 0);
            index_sample_1795 = result_2056[1];
            sample_sample_1794 = result_2056[0];
            number mul_1796_2057 = sample_sample_1794 * sub_1760_2013;
            number mul_1797_2058 = mul_1796_2057 * sqrt_1749_2003;
            number gen_1798_2059 = mul_1797_2058;
            number mul_1799_2060 = mul_1796_2057 * sqrt_1751_2005;
            number gen_1800_2061 = mul_1799_2060;
            number float_1805_2066 = float(0.5);
            number slide_1809_2071 = this->gen_01_slide_2070_next(clamp_1808_2069, this->sr / (number)100, this->sr / (number)100);
            number noise_1810_2073 = this->gen_01_noise_2072_next();
            number slide_1815_2079 = this->gen_01_slide_2078_next(clamp_1814_2077, this->sr / (number)100, this->sr / (number)100);
            number phasor_1816_2081 = this->gen_01_phasor_2080_next(slide_1815_2079, 0);
            number delta_1817_2083 = this->gen_01_delta_2082_next(phasor_1816_2081);
            number lt_1818_2084 = delta_1817_2083 < 0;
            number counter_1819 = 0;
            number counter_1820 = 0;
            number counter_1821 = 0;
            array<number, 3> result_2087 = this->gen_01_counter_2086_next(lt_1818_2084, Rst_1801_2062, int_1807_2068);
            counter_1821 = result_2087[2];
            counter_1820 = result_2087[1];
            counter_1819 = result_2087[0];
            number eq_1822_2088 = counter_1819 == clamp_1806_2067;
            number delta_1823_2090 = this->gen_01_delta_2089_next(eq_1822_2088);
            number eq_1824_2091 = delta_1823_2090 == 1;
            number gen_1825_2092 = eq_1824_2091;
            number latch_1826_2094 = this->gen_01_latch_2093_next(mstosamps_1813_2076, eq_1824_2091);
            number latch_1827_2096 = this->gen_01_latch_2095_next(noise_1810_2073, eq_1824_2091);
            number mul_1828_2097 = latch_1827_2096 * 0.5;
            number mul_1829_2098 = mul_1828_2097 * slide_1809_2071;
            number add_1830_2099 = mul_1829_2098 + 0.5;
            number sqrt_1831_2100 = (add_1830_2099 <= 0 ? 0 : rnbo_sqrt(add_1830_2099));
            number rsub_1832_2101 = 1 - add_1830_2099;
            number sqrt_1833_2102 = (rsub_1832_2101 <= 0 ? 0 : rnbo_sqrt(rsub_1832_2101));
            number counter_1834 = 0;
            number counter_1835 = 0;
            number counter_1836 = 0;
            array<number, 3> result_2104 = this->gen_01_counter_2103_next(int_1811_2074, eq_1824_2091, 0);
            counter_1836 = result_2104[2];
            counter_1835 = result_2104[1];
            counter_1834 = result_2104[0];
            auto min_1837_2105 = this->minimum(counter_1834, latch_1826_2094);
            number div_1838_2106 = (latch_1826_2094 == 0. ? 0. : min_1837_2105 / latch_1826_2094);
            number mul_1839_2107 = div_1838_2106 * 6.28318530717958647692;
            number cos_1840_2108 = rnbo_cos(mul_1839_2107);
            number mul_1841_2109 = cos_1840_2108 * 0.5;
            number sub_1842_2110 = float_1805_2066 - mul_1841_2109;
            number gen_1843_2111 = sub_1842_2110;
            number noise_1847_2116 = this->gen_01_noise_2115_next();
            number noise_1848_2118 = this->gen_01_noise_2117_next();
            number abs_1849_2119 = rnbo_abs(noise_1848_2118);
            number slide_1851_2122 = this->gen_01_slide_2121_next(clamp_1850_2120, this->sr / (number)100, this->sr / (number)100);
            number mul_1852_2123 = abs_1849_2119 * slide_1851_2122;
            auto scale_1858_2129 = this->scale(mul_1852_2123, 0, 1, 0, sub_1857_2128, 1);
            number slide_1860_2132 = this->gen_01_slide_2131_next(scale_1859_2130, this->sr / (number)100, this->sr / (number)100);
            number add_1861_2133 = slide_1860_2132 + scale_1858_2129;
            number latch_1862_2135 = this->gen_01_latch_2134_next(add_1861_2133, eq_1824_2091);
            number slide_1864_2139 = this->gen_01_slide_2138_next(clamp_1863_2136, this->sr / (number)100, this->sr / (number)100);
            number mul_1865_2140 = noise_1847_2116 * slide_1864_2139;
            number pow_1866_2141 = fixnan(rnbo_pow(int_1845_2113, mul_1865_2140));
            number slide_1868_2144 = this->gen_01_slide_2143_next(clamp_1867_2142, this->sr / (number)100, this->sr / (number)100);
            number round_1869_2145 = rnbo_fround(slide_1868_2144 * 1 / (number)1) * 1;
            number div_1870_2146 = round_1869_2145 / (number)12;
            number pow_1871_2147 = fixnan(rnbo_pow(int_1844_2112, div_1870_2146));
            number mul_1872_2148 = pow_1871_2147 * pow_1866_2141;
            number latch_1873_2150 = this->gen_01_latch_2149_next(mul_1872_2148, eq_1824_2091);
            number mul_1874_2151 = min_1837_2105 * latch_1873_2150;
            number add_1875_2152 = mul_1874_2151 + latch_1862_2135;
            number sample_sample_1876 = 0;
            number index_sample_1877 = 0;
            auto result_2153 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1875_2152, 0);
            index_sample_1877 = result_2153[1];
            sample_sample_1876 = result_2153[0];
            number mul_1878_2154 = sample_sample_1876 * sub_1842_2110;
            number mul_1879_2155 = mul_1878_2154 * sqrt_1833_2102;
            number gen_1880_2156 = mul_1879_2155;
            number mul_1881_2157 = mul_1878_2154 * sqrt_1831_2100;
            number gen_1882_2158 = mul_1881_2157;
            number float_1887_2163 = float(0.5);
            number slide_1891_2168 = this->gen_01_slide_2167_next(clamp_1890_2166, this->sr / (number)100, this->sr / (number)100);
            number noise_1892_2170 = this->gen_01_noise_2169_next();
            number slide_1900_2179 = this->gen_01_slide_2178_next(clamp_1899_2177, this->sr / (number)100, this->sr / (number)100);
            number phasor_1901_2181 = this->gen_01_phasor_2180_next(slide_1900_2179, 0);
            number delta_1902_2183 = this->gen_01_delta_2182_next(phasor_1901_2181);
            number lt_1903_2184 = delta_1902_2183 < 0;
            number counter_1904 = 0;
            number counter_1905 = 0;
            number counter_1906 = 0;
            array<number, 3> result_2186 = this->gen_01_counter_2185_next(lt_1903_2184, Rst_1883_2159, int_1889_2165);
            counter_1906 = result_2186[2];
            counter_1905 = result_2186[1];
            counter_1904 = result_2186[0];
            number eq_1907_2187 = counter_1904 == clamp_1888_2164;
            number delta_1908_2189 = this->gen_01_delta_2188_next(eq_1907_2187);
            number eq_1909_2190 = delta_1908_2189 == 1;
            number gen_1910_2191 = eq_1909_2190;
            number latch_1911_2193 = this->gen_01_latch_2192_next(mstosamps_1895_2173, eq_1909_2190);
            number latch_1912_2195 = this->gen_01_latch_2194_next(noise_1892_2170, eq_1909_2190);
            number mul_1913_2196 = latch_1912_2195 * 0.5;
            number mul_1914_2197 = mul_1913_2196 * slide_1891_2168;
            number add_1915_2198 = mul_1914_2197 + 0.5;
            number sqrt_1916_2199 = (add_1915_2198 <= 0 ? 0 : rnbo_sqrt(add_1915_2198));
            number rsub_1917_2200 = 1 - add_1915_2198;
            number sqrt_1918_2201 = (rsub_1917_2200 <= 0 ? 0 : rnbo_sqrt(rsub_1917_2200));
            number counter_1919 = 0;
            number counter_1920 = 0;
            number counter_1921 = 0;
            array<number, 3> result_2203 = this->gen_01_counter_2202_next(int_1893_2171, eq_1909_2190, 0);
            counter_1921 = result_2203[2];
            counter_1920 = result_2203[1];
            counter_1919 = result_2203[0];
            auto min_1922_2204 = this->minimum(counter_1919, latch_1911_2193);
            number div_1923_2205 = (latch_1911_2193 == 0. ? 0. : min_1922_2204 / latch_1911_2193);
            number mul_1924_2206 = div_1923_2205 * 6.28318530717958647692;
            number cos_1925_2207 = rnbo_cos(mul_1924_2206);
            number mul_1926_2208 = cos_1925_2207 * 0.5;
            number sub_1927_2209 = float_1887_2163 - mul_1926_2208;
            number gen_1928_2210 = sub_1927_2209;
            number noise_1929_2212 = this->gen_01_noise_2211_next();
            number noise_1930_2214 = this->gen_01_noise_2213_next();
            number abs_1931_2215 = rnbo_abs(noise_1930_2214);
            number slide_1933_2218 = this->gen_01_slide_2217_next(clamp_1932_2216, this->sr / (number)100, this->sr / (number)100);
            number mul_1934_2219 = abs_1931_2215 * slide_1933_2218;
            auto scale_1940_2225 = this->scale(mul_1934_2219, 0, 1, 0, sub_1939_2224, 1);
            number slide_1942_2228 = this->gen_01_slide_2227_next(scale_1941_2226, this->sr / (number)100, this->sr / (number)100);
            number add_1943_2229 = slide_1942_2228 + scale_1940_2225;
            number latch_1944_2231 = this->gen_01_latch_2230_next(add_1943_2229, eq_1909_2190);
            number slide_1946_2234 = this->gen_01_slide_2233_next(clamp_1945_2232, this->sr / (number)100, this->sr / (number)100);
            number mul_1947_2235 = noise_1929_2212 * slide_1946_2234;
            number pow_1948_2236 = fixnan(rnbo_pow(int_1897_2175, mul_1947_2235));
            number slide_1950_2239 = this->gen_01_slide_2238_next(clamp_1949_2237, this->sr / (number)100, this->sr / (number)100);
            number round_1951_2240 = rnbo_fround(slide_1950_2239 * 1 / (number)1) * 1;
            number div_1952_2241 = round_1951_2240 / (number)12;
            number pow_1953_2242 = fixnan(rnbo_pow(int_1896_2174, div_1952_2241));
            number mul_1954_2243 = pow_1953_2242 * pow_1948_2236;
            number latch_1955_2245 = this->gen_01_latch_2244_next(mul_1954_2243, eq_1909_2190);
            number mul_1956_2246 = min_1922_2204 * latch_1955_2245;
            number add_1957_2247 = mul_1956_2246 + latch_1944_2231;
            number sample_sample_1958 = 0;
            number index_sample_1959 = 0;
            auto result_2248 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_1957_2247, 0);
            index_sample_1959 = result_2248[1];
            sample_sample_1958 = result_2248[0];
            number mul_1960_2249 = sample_sample_1958 * sub_1927_2209;
            number mul_1961_2250 = mul_1960_2249 * sqrt_1918_2201;
            number gen_1962_2251 = mul_1961_2250;
            number mul_1963_2252 = mul_1960_2249 * sqrt_1916_2199;
            number gen_1964_2253 = mul_1963_2252;
            number float_1969_2258 = float(0.5);
            number slide_1973_2263 = this->gen_01_slide_2262_next(clamp_1972_2261, this->sr / (number)100, this->sr / (number)100);
            number noise_1974_2265 = this->gen_01_noise_2264_next();
            number slide_1982_2274 = this->gen_01_slide_2273_next(clamp_1981_2272, this->sr / (number)100, this->sr / (number)100);
            number phasor_1983_2276 = this->gen_01_phasor_2275_next(slide_1982_2274, 0);
            number delta_1984_2278 = this->gen_01_delta_2277_next(phasor_1983_2276);
            number lt_1985_2279 = delta_1984_2278 < 0;
            number counter_1986 = 0;
            number counter_1987 = 0;
            number counter_1988 = 0;
            array<number, 3> result_2281 = this->gen_01_counter_2280_next(lt_1985_2279, Rst_1965_2254, int_1971_2260);
            counter_1988 = result_2281[2];
            counter_1987 = result_2281[1];
            counter_1986 = result_2281[0];
            number eq_1989_2282 = counter_1986 == clamp_1970_2259;
            number delta_1990_2284 = this->gen_01_delta_2283_next(eq_1989_2282);
            number eq_1991_2285 = delta_1990_2284 == 1;
            number gen_1992_2286 = eq_1991_2285;
            number latch_1993_2288 = this->gen_01_latch_2287_next(mstosamps_1977_2268, eq_1991_2285);
            number latch_1994_2290 = this->gen_01_latch_2289_next(noise_1974_2265, eq_1991_2285);
            number mul_1995_2291 = latch_1994_2290 * 0.5;
            number mul_1996_2292 = mul_1995_2291 * slide_1973_2263;
            number add_1997_2293 = mul_1996_2292 + 0.5;
            number sqrt_1998_2294 = (add_1997_2293 <= 0 ? 0 : rnbo_sqrt(add_1997_2293));
            number rsub_1999_2295 = 1 - add_1997_2293;
            number sqrt_2000_2296 = (rsub_1999_2295 <= 0 ? 0 : rnbo_sqrt(rsub_1999_2295));
            number counter_2001 = 0;
            number counter_2002 = 0;
            number counter_2003 = 0;
            array<number, 3> result_2298 = this->gen_01_counter_2297_next(int_1975_2266, eq_1991_2285, 0);
            counter_2003 = result_2298[2];
            counter_2002 = result_2298[1];
            counter_2001 = result_2298[0];
            auto min_2004_2299 = this->minimum(counter_2001, latch_1993_2288);
            number div_2005_2300 = (latch_1993_2288 == 0. ? 0. : min_2004_2299 / latch_1993_2288);
            number mul_2006_2301 = div_2005_2300 * 6.28318530717958647692;
            number cos_2007_2302 = rnbo_cos(mul_2006_2301);
            number mul_2008_2303 = cos_2007_2302 * 0.5;
            number sub_2009_2304 = float_1969_2258 - mul_2008_2303;
            number gen_2010_2305 = sub_2009_2304;
            number noise_2011_2307 = this->gen_01_noise_2306_next();
            number noise_2012_2309 = this->gen_01_noise_2308_next();
            number abs_2013_2310 = rnbo_abs(noise_2012_2309);
            number slide_2015_2313 = this->gen_01_slide_2312_next(clamp_2014_2311, this->sr / (number)100, this->sr / (number)100);
            number mul_2016_2314 = abs_2013_2310 * slide_2015_2313;
            auto scale_2022_2320 = this->scale(mul_2016_2314, 0, 1, 0, sub_2021_2319, 1);
            number slide_2024_2323 = this->gen_01_slide_2322_next(scale_2023_2321, this->sr / (number)100, this->sr / (number)100);
            number add_2025_2324 = slide_2024_2323 + scale_2022_2320;
            number latch_2026_2326 = this->gen_01_latch_2325_next(add_2025_2324, eq_1991_2285);
            number slide_2028_2329 = this->gen_01_slide_2328_next(clamp_2027_2327, this->sr / (number)100, this->sr / (number)100);
            number mul_2029_2330 = noise_2011_2307 * slide_2028_2329;
            number pow_2030_2331 = fixnan(rnbo_pow(int_1979_2270, mul_2029_2330));
            number slide_2032_2334 = this->gen_01_slide_2333_next(clamp_2031_2332, this->sr / (number)100, this->sr / (number)100);
            number round_2033_2335 = rnbo_fround(slide_2032_2334 * 1 / (number)1) * 1;
            number div_2034_2336 = round_2033_2335 / (number)12;
            number pow_2035_2337 = fixnan(rnbo_pow(int_1978_2269, div_2034_2336));
            number mul_2036_2338 = pow_2035_2337 * pow_2030_2331;
            number latch_2037_2340 = this->gen_01_latch_2339_next(mul_2036_2338, eq_1991_2285);
            number mul_2038_2341 = min_2004_2299 * latch_2037_2340;
            number add_2039_2342 = mul_2038_2341 + latch_2026_2326;
            number sample_sample_2040 = 0;
            number index_sample_2041 = 0;
            auto result_2343 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2039_2342, 0);
            index_sample_2041 = result_2343[1];
            sample_sample_2040 = result_2343[0];
            number mul_2042_2344 = sample_sample_2040 * sub_2009_2304;
            number mul_2043_2345 = mul_2042_2344 * sqrt_2000_2296;
            number gen_2044_2346 = mul_2043_2345;
            number mul_2045_2347 = mul_2042_2344 * sqrt_1998_2294;
            number gen_2046_2348 = mul_2045_2347;
            number float_2051_2353 = float(0.5);
            number slide_2055_2358 = this->gen_01_slide_2357_next(clamp_2054_2356, this->sr / (number)100, this->sr / (number)100);
            number noise_2056_2360 = this->gen_01_noise_2359_next();
            number slide_2064_2369 = this->gen_01_slide_2368_next(clamp_2063_2367, this->sr / (number)100, this->sr / (number)100);
            number phasor_2065_2371 = this->gen_01_phasor_2370_next(slide_2064_2369, 0);
            number delta_2066_2373 = this->gen_01_delta_2372_next(phasor_2065_2371);
            number lt_2067_2374 = delta_2066_2373 < 0;
            number counter_2068 = 0;
            number counter_2069 = 0;
            number counter_2070 = 0;
            array<number, 3> result_2376 = this->gen_01_counter_2375_next(lt_2067_2374, Rst_2047_2349, int_2053_2355);
            counter_2070 = result_2376[2];
            counter_2069 = result_2376[1];
            counter_2068 = result_2376[0];
            number eq_2071_2377 = counter_2068 == clamp_2052_2354;
            number delta_2072_2379 = this->gen_01_delta_2378_next(eq_2071_2377);
            number eq_2073_2380 = delta_2072_2379 == 1;
            number gen_2074_2381 = eq_2073_2380;
            number latch_2075_2383 = this->gen_01_latch_2382_next(mstosamps_2059_2363, eq_2073_2380);
            number latch_2076_2385 = this->gen_01_latch_2384_next(noise_2056_2360, eq_2073_2380);
            number mul_2077_2386 = latch_2076_2385 * 0.5;
            number mul_2078_2387 = mul_2077_2386 * slide_2055_2358;
            number add_2079_2388 = mul_2078_2387 + 0.5;
            number sqrt_2080_2389 = (add_2079_2388 <= 0 ? 0 : rnbo_sqrt(add_2079_2388));
            number rsub_2081_2390 = 1 - add_2079_2388;
            number sqrt_2082_2391 = (rsub_2081_2390 <= 0 ? 0 : rnbo_sqrt(rsub_2081_2390));
            number counter_2083 = 0;
            number counter_2084 = 0;
            number counter_2085 = 0;
            array<number, 3> result_2393 = this->gen_01_counter_2392_next(int_2057_2361, eq_2073_2380, 0);
            counter_2085 = result_2393[2];
            counter_2084 = result_2393[1];
            counter_2083 = result_2393[0];
            auto min_2086_2394 = this->minimum(counter_2083, latch_2075_2383);
            number div_2087_2395 = (latch_2075_2383 == 0. ? 0. : min_2086_2394 / latch_2075_2383);
            number mul_2088_2396 = div_2087_2395 * 6.28318530717958647692;
            number cos_2089_2397 = rnbo_cos(mul_2088_2396);
            number mul_2090_2398 = cos_2089_2397 * 0.5;
            number sub_2091_2399 = float_2051_2353 - mul_2090_2398;
            number gen_2092_2400 = sub_2091_2399;
            number noise_2093_2402 = this->gen_01_noise_2401_next();
            number noise_2094_2404 = this->gen_01_noise_2403_next();
            number abs_2095_2405 = rnbo_abs(noise_2094_2404);
            number slide_2097_2408 = this->gen_01_slide_2407_next(clamp_2096_2406, this->sr / (number)100, this->sr / (number)100);
            number mul_2098_2409 = abs_2095_2405 * slide_2097_2408;
            auto scale_2104_2415 = this->scale(mul_2098_2409, 0, 1, 0, sub_2103_2414, 1);
            number slide_2106_2418 = this->gen_01_slide_2417_next(scale_2105_2416, this->sr / (number)100, this->sr / (number)100);
            number add_2107_2419 = slide_2106_2418 + scale_2104_2415;
            number latch_2108_2421 = this->gen_01_latch_2420_next(add_2107_2419, eq_2073_2380);
            number slide_2110_2424 = this->gen_01_slide_2423_next(clamp_2109_2422, this->sr / (number)100, this->sr / (number)100);
            number mul_2111_2425 = noise_2093_2402 * slide_2110_2424;
            number pow_2112_2426 = fixnan(rnbo_pow(int_2061_2365, mul_2111_2425));
            number slide_2114_2429 = this->gen_01_slide_2428_next(clamp_2113_2427, this->sr / (number)100, this->sr / (number)100);
            number round_2115_2430 = rnbo_fround(slide_2114_2429 * 1 / (number)1) * 1;
            number div_2116_2431 = round_2115_2430 / (number)12;
            number pow_2117_2432 = fixnan(rnbo_pow(int_2060_2364, div_2116_2431));
            number mul_2118_2433 = pow_2117_2432 * pow_2112_2426;
            number latch_2119_2435 = this->gen_01_latch_2434_next(mul_2118_2433, eq_2073_2380);
            number mul_2120_2436 = min_2086_2394 * latch_2119_2435;
            number add_2121_2437 = mul_2120_2436 + latch_2108_2421;
            number sample_sample_2122 = 0;
            number index_sample_2123 = 0;
            auto result_2438 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2121_2437, 0);
            index_sample_2123 = result_2438[1];
            sample_sample_2122 = result_2438[0];
            number mul_2124_2439 = sample_sample_2122 * sub_2091_2399;
            number mul_2125_2440 = mul_2124_2439 * sqrt_2080_2389;
            number gen_2126_2441 = mul_2125_2440;
            number mul_2127_2442 = mul_2124_2439 * sqrt_2082_2391;
            number gen_2128_2443 = mul_2127_2442;
            number float_2133_2448 = float(0.5);
            number slide_2137_2453 = this->gen_01_slide_2452_next(clamp_2136_2451, this->sr / (number)100, this->sr / (number)100);
            number noise_2138_2455 = this->gen_01_noise_2454_next();
            number slide_2146_2464 = this->gen_01_slide_2463_next(clamp_2145_2462, this->sr / (number)100, this->sr / (number)100);
            number phasor_2147_2466 = this->gen_01_phasor_2465_next(slide_2146_2464, 0);
            number delta_2148_2468 = this->gen_01_delta_2467_next(phasor_2147_2466);
            number lt_2149_2469 = delta_2148_2468 < 0;
            number counter_2150 = 0;
            number counter_2151 = 0;
            number counter_2152 = 0;
            array<number, 3> result_2471 = this->gen_01_counter_2470_next(lt_2149_2469, Rst_2129_2444, int_2135_2450);
            counter_2152 = result_2471[2];
            counter_2151 = result_2471[1];
            counter_2150 = result_2471[0];
            number eq_2153_2472 = counter_2150 == clamp_2134_2449;
            number delta_2154_2474 = this->gen_01_delta_2473_next(eq_2153_2472);
            number eq_2155_2475 = delta_2154_2474 == 1;
            number gen_2156_2476 = eq_2155_2475;
            number latch_2157_2478 = this->gen_01_latch_2477_next(noise_2138_2455, eq_2155_2475);
            number mul_2158_2479 = latch_2157_2478 * 0.5;
            number mul_2159_2480 = mul_2158_2479 * slide_2137_2453;
            number add_2160_2481 = mul_2159_2480 + 0.5;
            number sqrt_2161_2482 = (add_2160_2481 <= 0 ? 0 : rnbo_sqrt(add_2160_2481));
            number rsub_2162_2483 = 1 - add_2160_2481;
            number sqrt_2163_2484 = (rsub_2162_2483 <= 0 ? 0 : rnbo_sqrt(rsub_2162_2483));
            number latch_2164_2487 = this->gen_01_latch_2486_next(mstosamps_2141_2458, eq_2155_2475);
            number counter_2165 = 0;
            number counter_2166 = 0;
            number counter_2167 = 0;
            array<number, 3> result_2489 = this->gen_01_counter_2488_next(int_2139_2456, eq_2155_2475, 0);
            counter_2167 = result_2489[2];
            counter_2166 = result_2489[1];
            counter_2165 = result_2489[0];
            auto min_2168_2490 = this->minimum(counter_2165, latch_2164_2487);
            number div_2169_2491 = (latch_2164_2487 == 0. ? 0. : min_2168_2490 / latch_2164_2487);
            number mul_2170_2492 = div_2169_2491 * 6.28318530717958647692;
            number cos_2171_2493 = rnbo_cos(mul_2170_2492);
            number mul_2172_2494 = cos_2171_2493 * 0.5;
            number sub_2173_2495 = float_2133_2448 - mul_2172_2494;
            number gen_2174_2496 = sub_2173_2495;
            number noise_2175_2498 = this->gen_01_noise_2497_next();
            number noise_2176_2500 = this->gen_01_noise_2499_next();
            number abs_2177_2501 = rnbo_abs(noise_2176_2500);
            number slide_2179_2504 = this->gen_01_slide_2503_next(clamp_2178_2502, this->sr / (number)100, this->sr / (number)100);
            number mul_2180_2505 = abs_2177_2501 * slide_2179_2504;
            auto scale_2186_2511 = this->scale(mul_2180_2505, 0, 1, 0, sub_2185_2510, 1);
            number slide_2188_2514 = this->gen_01_slide_2513_next(scale_2187_2512, this->sr / (number)100, this->sr / (number)100);
            number add_2189_2515 = slide_2188_2514 + scale_2186_2511;
            number latch_2190_2517 = this->gen_01_latch_2516_next(add_2189_2515, eq_2155_2475);
            number slide_2192_2520 = this->gen_01_slide_2519_next(clamp_2191_2518, this->sr / (number)100, this->sr / (number)100);
            number mul_2193_2521 = noise_2175_2498 * slide_2192_2520;
            number pow_2194_2522 = fixnan(rnbo_pow(int_2143_2460, mul_2193_2521));
            number slide_2196_2526 = this->gen_01_slide_2525_next(clamp_2195_2523, this->sr / (number)100, this->sr / (number)100);
            number round_2197_2527 = rnbo_fround(slide_2196_2526 * 1 / (number)1) * 1;
            number div_2198_2528 = round_2197_2527 / (number)12;
            number pow_2199_2529 = fixnan(rnbo_pow(int_2142_2459, div_2198_2528));
            number mul_2200_2530 = pow_2199_2529 * pow_2194_2522;
            number latch_2201_2532 = this->gen_01_latch_2531_next(mul_2200_2530, eq_2155_2475);
            number mul_2202_2533 = min_2168_2490 * latch_2201_2532;
            number add_2203_2534 = mul_2202_2533 + latch_2190_2517;
            number sample_sample_2204 = 0;
            number index_sample_2205 = 0;
            auto result_2535 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2203_2534, 0);
            index_sample_2205 = result_2535[1];
            sample_sample_2204 = result_2535[0];
            number mul_2206_2536 = sample_sample_2204 * sub_2173_2495;
            number mul_2207_2537 = mul_2206_2536 * sqrt_2163_2484;
            number gen_2208_2538 = mul_2207_2537;
            number mul_2209_2539 = mul_2206_2536 * sqrt_2161_2482;
            number gen_2210_2540 = mul_2209_2539;
            number float_2215_2545 = float(0.5);
            number slide_2219_2550 = this->gen_01_slide_2549_next(clamp_2218_2548, this->sr / (number)100, this->sr / (number)100);
            number noise_2220_2552 = this->gen_01_noise_2551_next();
            number slide_2228_2561 = this->gen_01_slide_2560_next(clamp_2227_2559, this->sr / (number)100, this->sr / (number)100);
            number phasor_2229_2563 = this->gen_01_phasor_2562_next(slide_2228_2561, 0);
            number delta_2230_2565 = this->gen_01_delta_2564_next(phasor_2229_2563);
            number lt_2231_2566 = delta_2230_2565 < 0;
            number counter_2232 = 0;
            number counter_2233 = 0;
            number counter_2234 = 0;
            array<number, 3> result_2568 = this->gen_01_counter_2567_next(lt_2231_2566, Rst_2211_2541, int_2217_2547);
            counter_2234 = result_2568[2];
            counter_2233 = result_2568[1];
            counter_2232 = result_2568[0];
            number eq_2235_2569 = counter_2232 == clamp_2216_2546;
            number delta_2236_2571 = this->gen_01_delta_2570_next(eq_2235_2569);
            number eq_2237_2572 = delta_2236_2571 == 1;
            number gen_2238_2573 = eq_2237_2572;
            number latch_2239_2575 = this->gen_01_latch_2574_next(noise_2220_2552, eq_2237_2572);
            number mul_2240_2576 = latch_2239_2575 * 0.5;
            number mul_2241_2577 = mul_2240_2576 * slide_2219_2550;
            number add_2242_2578 = mul_2241_2577 + 0.5;
            number sqrt_2243_2579 = (add_2242_2578 <= 0 ? 0 : rnbo_sqrt(add_2242_2578));
            number rsub_2244_2580 = 1 - add_2242_2578;
            number sqrt_2245_2581 = (rsub_2244_2580 <= 0 ? 0 : rnbo_sqrt(rsub_2244_2580));
            number latch_2246_2583 = this->gen_01_latch_2582_next(mstosamps_2223_2555, eq_2237_2572);
            number counter_2247 = 0;
            number counter_2248 = 0;
            number counter_2249 = 0;
            array<number, 3> result_2585 = this->gen_01_counter_2584_next(int_2221_2553, eq_2237_2572, 0);
            counter_2249 = result_2585[2];
            counter_2248 = result_2585[1];
            counter_2247 = result_2585[0];
            auto min_2250_2586 = this->minimum(counter_2247, latch_2246_2583);
            number div_2251_2587 = (latch_2246_2583 == 0. ? 0. : min_2250_2586 / latch_2246_2583);
            number mul_2252_2588 = div_2251_2587 * 6.28318530717958647692;
            number cos_2253_2589 = rnbo_cos(mul_2252_2588);
            number mul_2254_2590 = cos_2253_2589 * 0.5;
            number sub_2255_2591 = float_2215_2545 - mul_2254_2590;
            number gen_2256_2592 = sub_2255_2591;
            number noise_2257_2594 = this->gen_01_noise_2593_next();
            number noise_2258_2596 = this->gen_01_noise_2595_next();
            number abs_2259_2597 = rnbo_abs(noise_2258_2596);
            number slide_2261_2600 = this->gen_01_slide_2599_next(clamp_2260_2598, this->sr / (number)100, this->sr / (number)100);
            number mul_2262_2601 = abs_2259_2597 * slide_2261_2600;
            auto scale_2268_2607 = this->scale(mul_2262_2601, 0, 1, 0, sub_2267_2606, 1);
            number slide_2270_2610 = this->gen_01_slide_2609_next(scale_2269_2608, this->sr / (number)100, this->sr / (number)100);
            number add_2271_2611 = slide_2270_2610 + scale_2268_2607;
            number latch_2272_2613 = this->gen_01_latch_2612_next(add_2271_2611, eq_2237_2572);
            number slide_2274_2616 = this->gen_01_slide_2615_next(clamp_2273_2614, this->sr / (number)100, this->sr / (number)100);
            number mul_2275_2617 = noise_2257_2594 * slide_2274_2616;
            number pow_2276_2618 = fixnan(rnbo_pow(int_2225_2557, mul_2275_2617));
            number slide_2278_2621 = this->gen_01_slide_2620_next(clamp_2277_2619, this->sr / (number)100, this->sr / (number)100);
            number round_2279_2622 = rnbo_fround(slide_2278_2621 * 1 / (number)1) * 1;
            number div_2280_2623 = round_2279_2622 / (number)12;
            number pow_2281_2624 = fixnan(rnbo_pow(int_2224_2556, div_2280_2623));
            number mul_2282_2625 = pow_2281_2624 * pow_2276_2618;
            number latch_2283_2627 = this->gen_01_latch_2626_next(mul_2282_2625, eq_2237_2572);
            number mul_2284_2628 = min_2250_2586 * latch_2283_2627;
            number add_2285_2629 = mul_2284_2628 + latch_2272_2613;
            number sample_sample_2286 = 0;
            number index_sample_2287 = 0;
            auto result_2630 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2285_2629, 0);
            index_sample_2287 = result_2630[1];
            sample_sample_2286 = result_2630[0];
            number mul_2288_2631 = sample_sample_2286 * sub_2255_2591;
            number mul_2289_2632 = mul_2288_2631 * sqrt_2243_2579;
            number gen_2290_2633 = mul_2289_2632;
            number mul_2291_2634 = mul_2288_2631 * sqrt_2245_2581;
            number gen_2292_2635 = mul_2291_2634;
            number float_2297_2640 = float(0.5);
            number slide_2301_2645 = this->gen_01_slide_2644_next(clamp_2300_2643, this->sr / (number)100, this->sr / (number)100);
            number noise_2302_2647 = this->gen_01_noise_2646_next();
            number slide_2307_2653 = this->gen_01_slide_2652_next(clamp_2306_2651, this->sr / (number)100, this->sr / (number)100);
            number phasor_2308_2655 = this->gen_01_phasor_2654_next(slide_2307_2653, 0);
            number delta_2309_2657 = this->gen_01_delta_2656_next(phasor_2308_2655);
            number lt_2310_2658 = delta_2309_2657 < 0;
            number counter_2311 = 0;
            number counter_2312 = 0;
            number counter_2313 = 0;
            array<number, 3> result_2661 = this->gen_01_counter_2660_next(lt_2310_2658, Rst_2293_2636, int_2299_2642);
            counter_2313 = result_2661[2];
            counter_2312 = result_2661[1];
            counter_2311 = result_2661[0];
            number eq_2314_2662 = counter_2311 == clamp_2298_2641;
            number delta_2315_2664 = this->gen_01_delta_2663_next(eq_2314_2662);
            number eq_2316_2665 = delta_2315_2664 == 1;
            number gen_2317_2666 = eq_2316_2665;
            number latch_2318_2668 = this->gen_01_latch_2667_next(mstosamps_2305_2650, eq_2316_2665);
            number latch_2319_2670 = this->gen_01_latch_2669_next(noise_2302_2647, eq_2316_2665);
            number mul_2320_2671 = latch_2319_2670 * 0.5;
            number mul_2321_2672 = mul_2320_2671 * slide_2301_2645;
            number add_2322_2673 = mul_2321_2672 + 0.5;
            number sqrt_2323_2674 = (add_2322_2673 <= 0 ? 0 : rnbo_sqrt(add_2322_2673));
            number rsub_2324_2675 = 1 - add_2322_2673;
            number sqrt_2325_2676 = (rsub_2324_2675 <= 0 ? 0 : rnbo_sqrt(rsub_2324_2675));
            number counter_2326 = 0;
            number counter_2327 = 0;
            number counter_2328 = 0;
            array<number, 3> result_2678 = this->gen_01_counter_2677_next(int_2303_2648, eq_2316_2665, 0);
            counter_2328 = result_2678[2];
            counter_2327 = result_2678[1];
            counter_2326 = result_2678[0];
            auto min_2329_2679 = this->minimum(counter_2326, latch_2318_2668);
            number div_2330_2680 = (latch_2318_2668 == 0. ? 0. : min_2329_2679 / latch_2318_2668);
            number mul_2331_2681 = div_2330_2680 * 6.28318530717958647692;
            number cos_2332_2682 = rnbo_cos(mul_2331_2681);
            number mul_2333_2683 = cos_2332_2682 * 0.5;
            number sub_2334_2684 = float_2297_2640 - mul_2333_2683;
            number gen_2335_2685 = sub_2334_2684;
            number noise_2339_2690 = this->gen_01_noise_2689_next();
            number noise_2340_2692 = this->gen_01_noise_2691_next();
            number abs_2341_2693 = rnbo_abs(noise_2340_2692);
            number slide_2343_2696 = this->gen_01_slide_2695_next(clamp_2342_2694, this->sr / (number)100, this->sr / (number)100);
            number mul_2344_2697 = abs_2341_2693 * slide_2343_2696;
            auto scale_2350_2703 = this->scale(mul_2344_2697, 0, 1, 0, sub_2349_2702, 1);
            number slide_2352_2706 = this->gen_01_slide_2705_next(scale_2351_2704, this->sr / (number)100, this->sr / (number)100);
            number add_2353_2707 = slide_2352_2706 + scale_2350_2703;
            number latch_2354_2709 = this->gen_01_latch_2708_next(add_2353_2707, eq_2316_2665);
            number slide_2356_2712 = this->gen_01_slide_2711_next(clamp_2355_2710, this->sr / (number)100, this->sr / (number)100);
            number mul_2357_2713 = noise_2339_2690 * slide_2356_2712;
            number pow_2358_2714 = fixnan(rnbo_pow(int_2337_2687, mul_2357_2713));
            number slide_2360_2717 = this->gen_01_slide_2716_next(clamp_2359_2715, this->sr / (number)100, this->sr / (number)100);
            number round_2361_2718 = rnbo_fround(slide_2360_2717 * 1 / (number)1) * 1;
            number div_2362_2719 = round_2361_2718 / (number)12;
            number pow_2363_2720 = fixnan(rnbo_pow(int_2336_2686, div_2362_2719));
            number mul_2364_2721 = pow_2363_2720 * pow_2358_2714;
            number latch_2365_2723 = this->gen_01_latch_2722_next(mul_2364_2721, eq_2316_2665);
            number mul_2366_2724 = min_2329_2679 * latch_2365_2723;
            number add_2367_2725 = mul_2366_2724 + latch_2354_2709;
            number sample_sample_2368 = 0;
            number index_sample_2369 = 0;
            auto result_2726 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2367_2725, 0);
            index_sample_2369 = result_2726[1];
            sample_sample_2368 = result_2726[0];
            number mul_2370_2727 = sample_sample_2368 * sub_2334_2684;
            number mul_2371_2728 = mul_2370_2727 * sqrt_2325_2676;
            number gen_2372_2729 = mul_2371_2728;
            number mul_2373_2730 = mul_2370_2727 * sqrt_2323_2674;
            number gen_2374_2731 = mul_2373_2730;
            number float_2379_2736 = float(0.5);
            number slide_2383_2741 = this->gen_01_slide_2740_next(clamp_2382_2739, this->sr / (number)100, this->sr / (number)100);
            number noise_2384_2743 = this->gen_01_noise_2742_next();
            number slide_2392_2752 = this->gen_01_slide_2751_next(clamp_2391_2750, this->sr / (number)100, this->sr / (number)100);
            number phasor_2393_2754 = this->gen_01_phasor_2753_next(slide_2392_2752, 0);
            number delta_2394_2756 = this->gen_01_delta_2755_next(phasor_2393_2754);
            number lt_2395_2757 = delta_2394_2756 < 0;
            number counter_2396 = 0;
            number counter_2397 = 0;
            number counter_2398 = 0;
            array<number, 3> result_2759 = this->gen_01_counter_2758_next(lt_2395_2757, Rst_2375_2732, int_2381_2738);
            counter_2398 = result_2759[2];
            counter_2397 = result_2759[1];
            counter_2396 = result_2759[0];
            number eq_2399_2760 = counter_2396 == clamp_2380_2737;
            number delta_2400_2762 = this->gen_01_delta_2761_next(eq_2399_2760);
            number eq_2401_2763 = delta_2400_2762 == 1;
            number gen_2402_2764 = eq_2401_2763;
            number latch_2403_2766 = this->gen_01_latch_2765_next(noise_2384_2743, eq_2401_2763);
            number mul_2404_2767 = latch_2403_2766 * 0.5;
            number mul_2405_2768 = mul_2404_2767 * slide_2383_2741;
            number add_2406_2769 = mul_2405_2768 + 0.5;
            number sqrt_2407_2770 = (add_2406_2769 <= 0 ? 0 : rnbo_sqrt(add_2406_2769));
            number rsub_2408_2771 = 1 - add_2406_2769;
            number sqrt_2409_2772 = (rsub_2408_2771 <= 0 ? 0 : rnbo_sqrt(rsub_2408_2771));
            number latch_2410_2774 = this->gen_01_latch_2773_next(mstosamps_2387_2746, eq_2401_2763);
            number counter_2411 = 0;
            number counter_2412 = 0;
            number counter_2413 = 0;
            array<number, 3> result_2776 = this->gen_01_counter_2775_next(int_2385_2744, eq_2401_2763, 0);
            counter_2413 = result_2776[2];
            counter_2412 = result_2776[1];
            counter_2411 = result_2776[0];
            auto min_2414_2777 = this->minimum(counter_2411, latch_2410_2774);
            number div_2415_2778 = (latch_2410_2774 == 0. ? 0. : min_2414_2777 / latch_2410_2774);
            number mul_2416_2779 = div_2415_2778 * 6.28318530717958647692;
            number cos_2417_2780 = rnbo_cos(mul_2416_2779);
            number mul_2418_2781 = cos_2417_2780 * 0.5;
            number sub_2419_2782 = float_2379_2736 - mul_2418_2781;
            number gen_2420_2783 = sub_2419_2782;
            number noise_2421_2785 = this->gen_01_noise_2784_next();
            number noise_2422_2787 = this->gen_01_noise_2786_next();
            number abs_2423_2788 = rnbo_abs(noise_2422_2787);
            number slide_2425_2791 = this->gen_01_slide_2790_next(clamp_2424_2789, this->sr / (number)100, this->sr / (number)100);
            number mul_2426_2792 = abs_2423_2788 * slide_2425_2791;
            auto scale_2432_2798 = this->scale(mul_2426_2792, 0, 1, 0, sub_2431_2797, 1);
            number slide_2434_2801 = this->gen_01_slide_2800_next(scale_2433_2799, this->sr / (number)100, this->sr / (number)100);
            number add_2435_2802 = slide_2434_2801 + scale_2432_2798;
            number latch_2436_2804 = this->gen_01_latch_2803_next(add_2435_2802, eq_2401_2763);
            number slide_2438_2807 = this->gen_01_slide_2806_next(clamp_2437_2805, this->sr / (number)100, this->sr / (number)100);
            number mul_2439_2808 = noise_2421_2785 * slide_2438_2807;
            number pow_2440_2809 = fixnan(rnbo_pow(int_2389_2748, mul_2439_2808));
            number slide_2442_2812 = this->gen_01_slide_2811_next(clamp_2441_2810, this->sr / (number)100, this->sr / (number)100);
            number round_2443_2813 = rnbo_fround(slide_2442_2812 * 1 / (number)1) * 1;
            number div_2444_2814 = round_2443_2813 / (number)12;
            number pow_2445_2815 = fixnan(rnbo_pow(int_2388_2747, div_2444_2814));
            number mul_2446_2816 = pow_2445_2815 * pow_2440_2809;
            number latch_2447_2818 = this->gen_01_latch_2817_next(mul_2446_2816, eq_2401_2763);
            number mul_2448_2819 = min_2414_2777 * latch_2447_2818;
            number add_2449_2820 = mul_2448_2819 + latch_2436_2804;
            number sample_sample_2450 = 0;
            number index_sample_2451 = 0;
            auto result_2821 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2449_2820, 0);
            index_sample_2451 = result_2821[1];
            sample_sample_2450 = result_2821[0];
            number mul_2452_2822 = sample_sample_2450 * sub_2419_2782;
            number mul_2453_2823 = mul_2452_2822 * sqrt_2407_2770;
            number gen_2454_2824 = mul_2453_2823;
            number mul_2455_2825 = mul_2452_2822 * sqrt_2409_2772;
            number gen_2456_2826 = mul_2455_2825;
            number float_2461_2831 = float(0.5);
            number slide_2465_2836 = this->gen_01_slide_2835_next(clamp_2464_2834, this->sr / (number)100, this->sr / (number)100);
            number noise_2466_2838 = this->gen_01_noise_2837_next();
            number slide_2474_2847 = this->gen_01_slide_2846_next(clamp_2473_2845, this->sr / (number)100, this->sr / (number)100);
            number phasor_2475_2849 = this->gen_01_phasor_2848_next(slide_2474_2847, 0);
            number delta_2476_2851 = this->gen_01_delta_2850_next(phasor_2475_2849);
            number lt_2477_2852 = delta_2476_2851 < 0;
            number counter_2478 = 0;
            number counter_2479 = 0;
            number counter_2480 = 0;
            array<number, 3> result_2854 = this->gen_01_counter_2853_next(lt_2477_2852, Rst_2457_2827, int_2463_2833);
            counter_2480 = result_2854[2];
            counter_2479 = result_2854[1];
            counter_2478 = result_2854[0];
            number eq_2481_2855 = counter_2478 == clamp_2462_2832;
            number delta_2482_2857 = this->gen_01_delta_2856_next(eq_2481_2855);
            number eq_2483_2858 = delta_2482_2857 == 1;
            number gen_2484_2859 = eq_2483_2858;
            number latch_2485_2861 = this->gen_01_latch_2860_next(noise_2466_2838, eq_2483_2858);
            number mul_2486_2862 = latch_2485_2861 * 0.5;
            number mul_2487_2863 = mul_2486_2862 * slide_2465_2836;
            number add_2488_2864 = mul_2487_2863 + 0.5;
            number sqrt_2489_2865 = (add_2488_2864 <= 0 ? 0 : rnbo_sqrt(add_2488_2864));
            number rsub_2490_2866 = 1 - add_2488_2864;
            number sqrt_2491_2867 = (rsub_2490_2866 <= 0 ? 0 : rnbo_sqrt(rsub_2490_2866));
            number latch_2492_2869 = this->gen_01_latch_2868_next(mstosamps_2469_2841, eq_2483_2858);
            number counter_2493 = 0;
            number counter_2494 = 0;
            number counter_2495 = 0;
            array<number, 3> result_2871 = this->gen_01_counter_2870_next(int_2467_2839, eq_2483_2858, 0);
            counter_2495 = result_2871[2];
            counter_2494 = result_2871[1];
            counter_2493 = result_2871[0];
            auto min_2496_2872 = this->minimum(counter_2493, latch_2492_2869);
            number div_2497_2873 = (latch_2492_2869 == 0. ? 0. : min_2496_2872 / latch_2492_2869);
            number mul_2498_2874 = div_2497_2873 * 6.28318530717958647692;
            number cos_2499_2875 = rnbo_cos(mul_2498_2874);
            number mul_2500_2876 = cos_2499_2875 * 0.5;
            number sub_2501_2877 = float_2461_2831 - mul_2500_2876;
            number gen_2502_2878 = sub_2501_2877;
            number noise_2503_2880 = this->gen_01_noise_2879_next();
            number noise_2504_2882 = this->gen_01_noise_2881_next();
            number abs_2505_2883 = rnbo_abs(noise_2504_2882);
            number slide_2507_2886 = this->gen_01_slide_2885_next(clamp_2506_2884, this->sr / (number)100, this->sr / (number)100);
            number mul_2508_2887 = abs_2505_2883 * slide_2507_2886;
            auto scale_2514_2893 = this->scale(mul_2508_2887, 0, 1, 0, sub_2513_2892, 1);
            number slide_2516_2896 = this->gen_01_slide_2895_next(scale_2515_2894, this->sr / (number)100, this->sr / (number)100);
            number add_2517_2897 = slide_2516_2896 + scale_2514_2893;
            number latch_2518_2899 = this->gen_01_latch_2898_next(add_2517_2897, eq_2483_2858);
            number slide_2520_2902 = this->gen_01_slide_2901_next(clamp_2519_2900, this->sr / (number)100, this->sr / (number)100);
            number mul_2521_2903 = noise_2503_2880 * slide_2520_2902;
            number pow_2522_2904 = fixnan(rnbo_pow(int_2471_2843, mul_2521_2903));
            number slide_2524_2907 = this->gen_01_slide_2906_next(clamp_2523_2905, this->sr / (number)100, this->sr / (number)100);
            number round_2525_2908 = rnbo_fround(slide_2524_2907 * 1 / (number)1) * 1;
            number div_2526_2909 = round_2525_2908 / (number)12;
            number pow_2527_2910 = fixnan(rnbo_pow(int_2470_2842, div_2526_2909));
            number mul_2528_2911 = pow_2527_2910 * pow_2522_2904;
            number latch_2529_2913 = this->gen_01_latch_2912_next(mul_2528_2911, eq_2483_2858);
            number mul_2530_2914 = min_2496_2872 * latch_2529_2913;
            number add_2531_2915 = mul_2530_2914 + latch_2518_2899;
            number sample_sample_2532 = 0;
            number index_sample_2533 = 0;
            auto result_2916 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2531_2915, 0);
            index_sample_2533 = result_2916[1];
            sample_sample_2532 = result_2916[0];
            number mul_2534_2917 = sample_sample_2532 * sub_2501_2877;
            number mul_2535_2918 = mul_2534_2917 * sqrt_2491_2867;
            number gen_2536_2919 = mul_2535_2918;
            number mul_2537_2920 = mul_2534_2917 * sqrt_2489_2865;
            number gen_2538_2921 = mul_2537_2920;
            number float_2543_2926 = float(0.5);
            number slide_2547_2931 = this->gen_01_slide_2930_next(clamp_2546_2929, this->sr / (number)100, this->sr / (number)100);
            number noise_2548_2933 = this->gen_01_noise_2932_next();
            number slide_2553_2939 = this->gen_01_slide_2938_next(clamp_2552_2937, this->sr / (number)100, this->sr / (number)100);
            number phasor_2554_2941 = this->gen_01_phasor_2940_next(slide_2553_2939, 0);
            number delta_2555_2943 = this->gen_01_delta_2942_next(phasor_2554_2941);
            number lt_2556_2944 = delta_2555_2943 < 0;
            number counter_2557 = 0;
            number counter_2558 = 0;
            number counter_2559 = 0;
            array<number, 3> result_2946 = this->gen_01_counter_2945_next(lt_2556_2944, Rst_2539_2922, int_2545_2928);
            counter_2559 = result_2946[2];
            counter_2558 = result_2946[1];
            counter_2557 = result_2946[0];
            number eq_2560_2947 = counter_2557 == clamp_2544_2927;
            number delta_2561_2949 = this->gen_01_delta_2948_next(eq_2560_2947);
            number eq_2562_2950 = delta_2561_2949 == 1;
            number gen_2563_2951 = eq_2562_2950;
            number latch_2564_2953 = this->gen_01_latch_2952_next(mstosamps_2551_2936, eq_2562_2950);
            number latch_2565_2955 = this->gen_01_latch_2954_next(noise_2548_2933, eq_2562_2950);
            number mul_2566_2956 = latch_2565_2955 * 0.5;
            number mul_2567_2957 = mul_2566_2956 * slide_2547_2931;
            number add_2568_2958 = mul_2567_2957 + 0.5;
            number sqrt_2569_2959 = (add_2568_2958 <= 0 ? 0 : rnbo_sqrt(add_2568_2958));
            number rsub_2570_2960 = 1 - add_2568_2958;
            number sqrt_2571_2961 = (rsub_2570_2960 <= 0 ? 0 : rnbo_sqrt(rsub_2570_2960));
            number counter_2572 = 0;
            number counter_2573 = 0;
            number counter_2574 = 0;
            array<number, 3> result_2963 = this->gen_01_counter_2962_next(int_2549_2934, eq_2562_2950, 0);
            counter_2574 = result_2963[2];
            counter_2573 = result_2963[1];
            counter_2572 = result_2963[0];
            auto min_2575_2964 = this->minimum(counter_2572, latch_2564_2953);
            number div_2576_2965 = (latch_2564_2953 == 0. ? 0. : min_2575_2964 / latch_2564_2953);
            number mul_2577_2966 = div_2576_2965 * 6.28318530717958647692;
            number cos_2578_2967 = rnbo_cos(mul_2577_2966);
            number mul_2579_2968 = cos_2578_2967 * 0.5;
            number sub_2580_2969 = float_2543_2926 - mul_2579_2968;
            number gen_2581_2970 = sub_2580_2969;
            number noise_2585_2975 = this->gen_01_noise_2974_next();
            number noise_2586_2977 = this->gen_01_noise_2976_next();
            number abs_2587_2978 = rnbo_abs(noise_2586_2977);
            number slide_2589_2981 = this->gen_01_slide_2980_next(clamp_2588_2979, this->sr / (number)100, this->sr / (number)100);
            number mul_2590_2982 = abs_2587_2978 * slide_2589_2981;
            auto scale_2596_2988 = this->scale(mul_2590_2982, 0, 1, 0, sub_2595_2987, 1);
            number slide_2598_2991 = this->gen_01_slide_2990_next(scale_2597_2989, this->sr / (number)100, this->sr / (number)100);
            number add_2599_2992 = slide_2598_2991 + scale_2596_2988;
            number latch_2600_2994 = this->gen_01_latch_2993_next(add_2599_2992, eq_2562_2950);
            number slide_2602_2997 = this->gen_01_slide_2996_next(clamp_2601_2995, this->sr / (number)100, this->sr / (number)100);
            number mul_2603_2998 = noise_2585_2975 * slide_2602_2997;
            number pow_2604_2999 = fixnan(rnbo_pow(int_2583_2972, mul_2603_2998));
            number slide_2606_3002 = this->gen_01_slide_3001_next(clamp_2605_3000, this->sr / (number)100, this->sr / (number)100);
            number round_2607_3003 = rnbo_fround(slide_2606_3002 * 1 / (number)1) * 1;
            number div_2608_3004 = round_2607_3003 / (number)12;
            number pow_2609_3005 = fixnan(rnbo_pow(int_2582_2971, div_2608_3004));
            number mul_2610_3006 = pow_2609_3005 * pow_2604_2999;
            number latch_2611_3008 = this->gen_01_latch_3007_next(mul_2610_3006, eq_2562_2950);
            number mul_2612_3009 = min_2575_2964 * latch_2611_3008;
            number add_2613_3010 = mul_2612_3009 + latch_2600_2994;
            number sample_sample_2614 = 0;
            number index_sample_2615 = 0;
            auto result_3011 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2613_3010, 0);
            index_sample_2615 = result_3011[1];
            sample_sample_2614 = result_3011[0];
            number mul_2616_3012 = sample_sample_2614 * sub_2580_2969;
            number mul_2617_3013 = mul_2616_3012 * sqrt_2571_2961;
            number gen_2618_3014 = mul_2617_3013;
            number mul_2619_3015 = mul_2616_3012 * sqrt_2569_2959;
            number gen_2620_3016 = mul_2619_3015;
            number float_2625_3021 = float(0.5);
            number slide_2629_3026 = this->gen_01_slide_3025_next(clamp_2628_3024, this->sr / (number)100, this->sr / (number)100);
            number noise_2630_3028 = this->gen_01_noise_3027_next();
            number slide_2638_3037 = this->gen_01_slide_3036_next(clamp_2637_3035, this->sr / (number)100, this->sr / (number)100);
            number phasor_2639_3039 = this->gen_01_phasor_3038_next(slide_2638_3037, 0);
            number delta_2640_3041 = this->gen_01_delta_3040_next(phasor_2639_3039);
            number lt_2641_3042 = delta_2640_3041 < 0;
            number counter_2642 = 0;
            number counter_2643 = 0;
            number counter_2644 = 0;
            array<number, 3> result_3044 = this->gen_01_counter_3043_next(lt_2641_3042, Rst_2621_3017, int_2627_3023);
            counter_2644 = result_3044[2];
            counter_2643 = result_3044[1];
            counter_2642 = result_3044[0];
            number eq_2645_3045 = counter_2642 == clamp_2626_3022;
            number delta_2646_3047 = this->gen_01_delta_3046_next(eq_2645_3045);
            number eq_2647_3048 = delta_2646_3047 == 1;
            number gen_2648_3049 = eq_2647_3048;
            number latch_2649_3051 = this->gen_01_latch_3050_next(noise_2630_3028, eq_2647_3048);
            number mul_2650_3052 = latch_2649_3051 * 0.5;
            number mul_2651_3053 = mul_2650_3052 * slide_2629_3026;
            number add_2652_3054 = mul_2651_3053 + 0.5;
            number sqrt_2653_3055 = (add_2652_3054 <= 0 ? 0 : rnbo_sqrt(add_2652_3054));
            number rsub_2654_3056 = 1 - add_2652_3054;
            number sqrt_2655_3057 = (rsub_2654_3056 <= 0 ? 0 : rnbo_sqrt(rsub_2654_3056));
            number latch_2656_3059 = this->gen_01_latch_3058_next(mstosamps_2633_3031, eq_2647_3048);
            number counter_2657 = 0;
            number counter_2658 = 0;
            number counter_2659 = 0;
            array<number, 3> result_3061 = this->gen_01_counter_3060_next(int_2631_3029, eq_2647_3048, 0);
            counter_2659 = result_3061[2];
            counter_2658 = result_3061[1];
            counter_2657 = result_3061[0];
            auto min_2660_3062 = this->minimum(counter_2657, latch_2656_3059);
            number div_2661_3063 = (latch_2656_3059 == 0. ? 0. : min_2660_3062 / latch_2656_3059);
            number mul_2662_3064 = div_2661_3063 * 6.28318530717958647692;
            number cos_2663_3065 = rnbo_cos(mul_2662_3064);
            number mul_2664_3066 = cos_2663_3065 * 0.5;
            number sub_2665_3067 = float_2625_3021 - mul_2664_3066;
            number gen_2666_3068 = sub_2665_3067;
            number noise_2667_3070 = this->gen_01_noise_3069_next();
            number noise_2668_3072 = this->gen_01_noise_3071_next();
            number abs_2669_3073 = rnbo_abs(noise_2668_3072);
            number slide_2671_3076 = this->gen_01_slide_3075_next(clamp_2670_3074, this->sr / (number)100, this->sr / (number)100);
            number mul_2672_3077 = abs_2669_3073 * slide_2671_3076;
            auto scale_2678_3083 = this->scale(mul_2672_3077, 0, 1, 0, sub_2677_3082, 1);
            number slide_2680_3086 = this->gen_01_slide_3085_next(scale_2679_3084, this->sr / (number)100, this->sr / (number)100);
            number add_2681_3087 = slide_2680_3086 + scale_2678_3083;
            number latch_2682_3089 = this->gen_01_latch_3088_next(add_2681_3087, eq_2647_3048);
            number slide_2684_3092 = this->gen_01_slide_3091_next(clamp_2683_3090, this->sr / (number)100, this->sr / (number)100);
            number mul_2685_3093 = noise_2667_3070 * slide_2684_3092;
            number pow_2686_3094 = fixnan(rnbo_pow(int_2635_3033, mul_2685_3093));
            number slide_2688_3097 = this->gen_01_slide_3096_next(clamp_2687_3095, this->sr / (number)100, this->sr / (number)100);
            number round_2689_3098 = rnbo_fround(slide_2688_3097 * 1 / (number)1) * 1;
            number div_2690_3099 = round_2689_3098 / (number)12;
            number pow_2691_3100 = fixnan(rnbo_pow(int_2634_3032, div_2690_3099));
            number mul_2692_3101 = pow_2691_3100 * pow_2686_3094;
            number latch_2693_3103 = this->gen_01_latch_3102_next(mul_2692_3101, eq_2647_3048);
            number mul_2694_3104 = min_2660_3062 * latch_2693_3103;
            number add_2695_3105 = mul_2694_3104 + latch_2682_3089;
            number sample_sample_2696 = 0;
            number index_sample_2697 = 0;
            auto result_3106 = this->peek_boundmode_wrap_interp_cubic(this->gen_01_sample, add_2695_3105, 0);
            index_sample_2697 = result_3106[1];
            sample_sample_2696 = result_3106[0];
            number mul_2698_3107 = sample_sample_2696 * sub_2665_3067;
            number mul_2699_3108 = mul_2698_3107 * sqrt_2653_3055;
            number gen_2700_3109 = mul_2699_3108;
            number mul_2701_3110 = mul_2698_3107 * sqrt_2655_3057;
            number gen_2702_3111 = mul_2701_3110;
            number R_2703_3112 = gen_2700_3109 + gen_2620_3016 + gen_2538_2921 + gen_2454_2824 + gen_2374_2731 + gen_2290_2633 + gen_2210_2540 + gen_2126_2441 + gen_2046_2348 + gen_1964_2253 + gen_1882_2158 + gen_1798_2059 + gen_1718_1963 + gen_1636_1867 + gen_1554_1772 + gen_1472_1676 + gen_324_337 + gen_1388_1578 + gen_1306_1483 + gen_1224_1387 + gen_1144_1293 + gen_1060_1195 + gen_978_1099 + gen_898_1006 + gen_816_911 + gen_734_815 + gen_652_719 + gen_570_624 + gen_488_528 + gen_404_430;
            out2[(Index)i] = R_2703_3112;
            number L_2704_3113 = gen_2702_3111 + gen_2618_3014 + gen_2536_2919 + gen_2456_2826 + gen_2372_2729 + gen_2292_2635 + gen_2208_2538 + gen_2128_2443 + gen_2044_2346 + gen_1962_2251 + gen_1880_2156 + gen_1800_2061 + gen_1716_1961 + gen_1634_1865 + gen_1552_1770 + gen_1470_1674 + gen_322_335 + gen_1390_1580 + gen_1308_1485 + gen_1226_1389 + gen_1142_1291 + gen_1062_1197 + gen_980_1101 + gen_896_1004 + gen_814_909 + gen_732_813 + gen_650_717 + gen_568_622 + gen_486_526 + gen_406_432;
            out1[(Index)i] = L_2704_3113;
        }
    }
    
    void adsr_01_perform(
        number attack,
        number decay,
        number sustain,
        number release,
        const SampleValue * trigger_signal,
        SampleValue * out,
        Index n
    ) {
        RNBO_UNUSED(trigger_signal);
        auto __adsr_01_trigger_number = this->adsr_01_trigger_number;
        auto __adsr_01_time = this->adsr_01_time;
        auto __adsr_01_amplitude = this->adsr_01_amplitude;
        auto __adsr_01_outval = this->adsr_01_outval;
        auto __adsr_01_startingpoint = this->adsr_01_startingpoint;
        auto __adsr_01_phase = this->adsr_01_phase;
        auto __adsr_01_legato = this->adsr_01_legato;
        auto __adsr_01_lastTriggerVal = this->adsr_01_lastTriggerVal;
        auto __adsr_01_maxsustain = this->adsr_01_maxsustain;
        auto __adsr_01_mspersamp = this->adsr_01_mspersamp;
        bool bangMute = false;
    
        for (Index i = 0; i < n; i++) {
            number clampedattack = (attack > __adsr_01_mspersamp ? attack : __adsr_01_mspersamp);
            number clampeddecay = (decay > __adsr_01_mspersamp ? decay : __adsr_01_mspersamp);
            number clampedsustain = (__adsr_01_maxsustain > __adsr_01_mspersamp ? __adsr_01_maxsustain : __adsr_01_mspersamp);
            number clampedrelease = (release > __adsr_01_mspersamp ? release : __adsr_01_mspersamp);
            number currentTriggerVal = this->adsr_01_triggerValueBuf[(Index)i];
    
            if ((__adsr_01_lastTriggerVal == 0.0 && currentTriggerVal != 0.0) || this->adsr_01_triggerBuf[(Index)i] == 1) {
                if ((bool)(__adsr_01_legato)) {
                    if (__adsr_01_phase != 0) {
                        __adsr_01_startingpoint = __adsr_01_outval;
                    } else {
                        __adsr_01_startingpoint = 0;
                    }
                } else {
                    __adsr_01_startingpoint = 0;
                }
    
                __adsr_01_amplitude = currentTriggerVal;
                __adsr_01_phase = 3;
                __adsr_01_time = 0.0;
                bangMute = false;
            } else if (__adsr_01_lastTriggerVal != 0.0 && currentTriggerVal == 0.0) {
                if (__adsr_01_phase != 4 && __adsr_01_phase != 0) {
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                    __adsr_01_time = 0.0;
                }
            }
    
            __adsr_01_time += __adsr_01_mspersamp;
    
            if (__adsr_01_phase == 0) {
                __adsr_01_outval = 0;
            } else if (__adsr_01_phase == 3) {
                if (__adsr_01_time > clampedattack) {
                    __adsr_01_time -= clampedattack;
                    __adsr_01_phase = 2;
                    __adsr_01_outval = __adsr_01_amplitude;
                } else {
                    __adsr_01_outval = (__adsr_01_amplitude - __adsr_01_startingpoint) * __adsr_01_time / clampedattack + __adsr_01_startingpoint;
                }
            } else if (__adsr_01_phase == 2) {
                if (__adsr_01_time > clampeddecay) {
                    __adsr_01_time -= clampeddecay;
                    __adsr_01_phase = 1;
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain + (__adsr_01_amplitude - __adsr_01_amplitude * sustain) * (1. - __adsr_01_time / clampeddecay);
                }
            } else if (__adsr_01_phase == 1) {
                if (__adsr_01_time > clampedsustain && __adsr_01_maxsustain > -1) {
                    __adsr_01_time -= clampedsustain;
                    __adsr_01_phase = 4;
                    __adsr_01_amplitude = __adsr_01_outval;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * sustain;
                }
            } else if (__adsr_01_phase == 4) {
                if (__adsr_01_time > clampedrelease) {
                    __adsr_01_time = 0;
                    __adsr_01_phase = 0;
                    __adsr_01_outval = 0;
                    __adsr_01_amplitude = 0;
                    bangMute = true;
                } else {
                    __adsr_01_outval = __adsr_01_amplitude * (1.0 - __adsr_01_time / clampedrelease);
                }
            }
    
            out[(Index)i] = __adsr_01_outval;
            this->adsr_01_triggerBuf[(Index)i] = 0;
            this->adsr_01_triggerValueBuf[(Index)i] = __adsr_01_trigger_number;
            __adsr_01_lastTriggerVal = currentTriggerVal;
        }
    
        if ((bool)(bangMute)) {
            this->getEngine()->scheduleClockEventWithValue(
                this,
                -1468824490,
                this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
                0
            );;
        }
    
        this->adsr_01_lastTriggerVal = __adsr_01_lastTriggerVal;
        this->adsr_01_phase = __adsr_01_phase;
        this->adsr_01_startingpoint = __adsr_01_startingpoint;
        this->adsr_01_outval = __adsr_01_outval;
        this->adsr_01_amplitude = __adsr_01_amplitude;
        this->adsr_01_time = __adsr_01_time;
    }
    
    void dspexpr_01_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_01_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void signaladder_02_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void dspexpr_02_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2[(Index)i];//#map:_###_obj_###_:1
        }
    }
    
    void signaladder_03_perform(
        const SampleValue * in1,
        const SampleValue * in2,
        SampleValue * out,
        Index n
    ) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out[(Index)i] = in1[(Index)i] + in2[(Index)i];
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    void data_01_srout_set(number ) {}
    
    void data_01_chanout_set(number ) {}
    
    void data_01_sizeout_set(number v) {
        this->data_01_sizeout = v;
    }
    
    number gen_01_slide_250_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_250_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_250_prev = this->gen_01_slide_250_prev + ((x > this->gen_01_slide_250_prev ? iup : idown)) * temp;
        return this->gen_01_slide_250_prev;
    }
    
    void gen_01_slide_250_reset() {
        this->gen_01_slide_250_prev = 0;
    }
    
    void gen_01_noise_253_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_253_state
        );
    }
    
    void gen_01_noise_253_init() {
        this->gen_01_noise_253_reset();
    }
    
    void gen_01_noise_253_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_253_state);
    }
    
    number gen_01_noise_253_next() {
        return xoshiro_next(this->gen_01_noise_253_state);
    }
    
    number gen_01_slide_262_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_262_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_262_prev = this->gen_01_slide_262_prev + ((x > this->gen_01_slide_262_prev ? iup : idown)) * temp;
        return this->gen_01_slide_262_prev;
    }
    
    void gen_01_slide_262_reset() {
        this->gen_01_slide_262_prev = 0;
    }
    
    number gen_01_phasor_264_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_264_conv;
    
        if (this->gen_01_phasor_264_currentPhase < 0.)
            this->gen_01_phasor_264_currentPhase = 1. + this->gen_01_phasor_264_currentPhase;
    
        if (this->gen_01_phasor_264_currentPhase > 1.)
            this->gen_01_phasor_264_currentPhase = this->gen_01_phasor_264_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_264_currentPhase;
        this->gen_01_phasor_264_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_264_reset() {
        this->gen_01_phasor_264_currentPhase = 0;
    }
    
    void gen_01_phasor_264_dspsetup() {
        this->gen_01_phasor_264_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_266_next(number x) {
        number temp = (number)(x - this->gen_01_delta_266_prev);
        this->gen_01_delta_266_prev = x;
        return temp;
    }
    
    void gen_01_delta_266_dspsetup() {
        this->gen_01_delta_266_reset();
    }
    
    void gen_01_delta_266_reset() {
        this->gen_01_delta_266_prev = 0;
    }
    
    array<number, 3> gen_01_counter_269_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_269_count = 0;
            this->gen_01_counter_269_carry = 0;
        } else {
            this->gen_01_counter_269_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_269_count >= limit) || (a < 0 && this->gen_01_counter_269_count <= limit)) {
                    this->gen_01_counter_269_count = 0;
                    this->gen_01_counter_269_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_269_count, carry_flag, this->gen_01_counter_269_carry};
    }
    
    void gen_01_counter_269_init() {
        this->gen_01_counter_269_count = 0;
    }
    
    void gen_01_counter_269_reset() {
        this->gen_01_counter_269_carry = 0;
        this->gen_01_counter_269_count = 0;
    }
    
    number gen_01_delta_272_next(number x) {
        number temp = (number)(x - this->gen_01_delta_272_prev);
        this->gen_01_delta_272_prev = x;
        return temp;
    }
    
    void gen_01_delta_272_dspsetup() {
        this->gen_01_delta_272_reset();
    }
    
    void gen_01_delta_272_reset() {
        this->gen_01_delta_272_prev = 0;
    }
    
    number gen_01_latch_276_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_276_value = x;
        }
    
        return this->gen_01_latch_276_value;
    }
    
    void gen_01_latch_276_dspsetup() {
        this->gen_01_latch_276_reset();
    }
    
    void gen_01_latch_276_init() {
        this->gen_01_latch_276_reset();
    }
    
    void gen_01_latch_276_reset() {
        this->gen_01_latch_276_value = 0;
    }
    
    number gen_01_latch_278_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_278_value = x;
        }
    
        return this->gen_01_latch_278_value;
    }
    
    void gen_01_latch_278_dspsetup() {
        this->gen_01_latch_278_reset();
    }
    
    void gen_01_latch_278_init() {
        this->gen_01_latch_278_reset();
    }
    
    void gen_01_latch_278_reset() {
        this->gen_01_latch_278_value = 0;
    }
    
    array<number, 3> gen_01_counter_286_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_286_count = 0;
            this->gen_01_counter_286_carry = 0;
        } else {
            this->gen_01_counter_286_count += a;
        }
    
        return {this->gen_01_counter_286_count, carry_flag, this->gen_01_counter_286_carry};
    }
    
    void gen_01_counter_286_init() {
        this->gen_01_counter_286_count = 0;
    }
    
    void gen_01_counter_286_reset() {
        this->gen_01_counter_286_carry = 0;
        this->gen_01_counter_286_count = 0;
    }
    
    void gen_01_noise_295_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_295_state
        );
    }
    
    void gen_01_noise_295_init() {
        this->gen_01_noise_295_reset();
    }
    
    void gen_01_noise_295_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_295_state);
    }
    
    number gen_01_noise_295_next() {
        return xoshiro_next(this->gen_01_noise_295_state);
    }
    
    void gen_01_noise_297_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_297_state
        );
    }
    
    void gen_01_noise_297_init() {
        this->gen_01_noise_297_reset();
    }
    
    void gen_01_noise_297_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_297_state);
    }
    
    number gen_01_noise_297_next() {
        return xoshiro_next(this->gen_01_noise_297_state);
    }
    
    number gen_01_slide_301_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_301_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_301_prev = this->gen_01_slide_301_prev + ((x > this->gen_01_slide_301_prev ? iup : idown)) * temp;
        return this->gen_01_slide_301_prev;
    }
    
    void gen_01_slide_301_reset() {
        this->gen_01_slide_301_prev = 0;
    }
    
    number gen_01_slide_311_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_311_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_311_prev = this->gen_01_slide_311_prev + ((x > this->gen_01_slide_311_prev ? iup : idown)) * temp;
        return this->gen_01_slide_311_prev;
    }
    
    void gen_01_slide_311_reset() {
        this->gen_01_slide_311_prev = 0;
    }
    
    number gen_01_latch_314_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_314_value = x;
        }
    
        return this->gen_01_latch_314_value;
    }
    
    void gen_01_latch_314_dspsetup() {
        this->gen_01_latch_314_reset();
    }
    
    void gen_01_latch_314_init() {
        this->gen_01_latch_314_reset();
    }
    
    void gen_01_latch_314_reset() {
        this->gen_01_latch_314_value = 0;
    }
    
    number gen_01_slide_317_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_317_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_317_prev = this->gen_01_slide_317_prev + ((x > this->gen_01_slide_317_prev ? iup : idown)) * temp;
        return this->gen_01_slide_317_prev;
    }
    
    void gen_01_slide_317_reset() {
        this->gen_01_slide_317_prev = 0;
    }
    
    number gen_01_slide_322_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_322_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_322_prev = this->gen_01_slide_322_prev + ((x > this->gen_01_slide_322_prev ? iup : idown)) * temp;
        return this->gen_01_slide_322_prev;
    }
    
    void gen_01_slide_322_reset() {
        this->gen_01_slide_322_prev = 0;
    }
    
    number gen_01_latch_328_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_328_value = x;
        }
    
        return this->gen_01_latch_328_value;
    }
    
    void gen_01_latch_328_dspsetup() {
        this->gen_01_latch_328_reset();
    }
    
    void gen_01_latch_328_init() {
        this->gen_01_latch_328_reset();
    }
    
    void gen_01_latch_328_reset() {
        this->gen_01_latch_328_value = 0;
    }
    
    number gen_01_slide_346_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_346_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_346_prev = this->gen_01_slide_346_prev + ((x > this->gen_01_slide_346_prev ? iup : idown)) * temp;
        return this->gen_01_slide_346_prev;
    }
    
    void gen_01_slide_346_reset() {
        this->gen_01_slide_346_prev = 0;
    }
    
    void gen_01_noise_348_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_348_state
        );
    }
    
    void gen_01_noise_348_init() {
        this->gen_01_noise_348_reset();
    }
    
    void gen_01_noise_348_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_348_state);
    }
    
    number gen_01_noise_348_next() {
        return xoshiro_next(this->gen_01_noise_348_state);
    }
    
    number gen_01_slide_354_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_354_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_354_prev = this->gen_01_slide_354_prev + ((x > this->gen_01_slide_354_prev ? iup : idown)) * temp;
        return this->gen_01_slide_354_prev;
    }
    
    void gen_01_slide_354_reset() {
        this->gen_01_slide_354_prev = 0;
    }
    
    number gen_01_phasor_356_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_356_conv;
    
        if (this->gen_01_phasor_356_currentPhase < 0.)
            this->gen_01_phasor_356_currentPhase = 1. + this->gen_01_phasor_356_currentPhase;
    
        if (this->gen_01_phasor_356_currentPhase > 1.)
            this->gen_01_phasor_356_currentPhase = this->gen_01_phasor_356_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_356_currentPhase;
        this->gen_01_phasor_356_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_356_reset() {
        this->gen_01_phasor_356_currentPhase = 0;
    }
    
    void gen_01_phasor_356_dspsetup() {
        this->gen_01_phasor_356_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_358_next(number x) {
        number temp = (number)(x - this->gen_01_delta_358_prev);
        this->gen_01_delta_358_prev = x;
        return temp;
    }
    
    void gen_01_delta_358_dspsetup() {
        this->gen_01_delta_358_reset();
    }
    
    void gen_01_delta_358_reset() {
        this->gen_01_delta_358_prev = 0;
    }
    
    array<number, 3> gen_01_counter_361_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_361_count = 0;
            this->gen_01_counter_361_carry = 0;
        } else {
            this->gen_01_counter_361_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_361_count >= limit) || (a < 0 && this->gen_01_counter_361_count <= limit)) {
                    this->gen_01_counter_361_count = 0;
                    this->gen_01_counter_361_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_361_count, carry_flag, this->gen_01_counter_361_carry};
    }
    
    void gen_01_counter_361_init() {
        this->gen_01_counter_361_count = 0;
    }
    
    void gen_01_counter_361_reset() {
        this->gen_01_counter_361_carry = 0;
        this->gen_01_counter_361_count = 0;
    }
    
    number gen_01_delta_364_next(number x) {
        number temp = (number)(x - this->gen_01_delta_364_prev);
        this->gen_01_delta_364_prev = x;
        return temp;
    }
    
    void gen_01_delta_364_dspsetup() {
        this->gen_01_delta_364_reset();
    }
    
    void gen_01_delta_364_reset() {
        this->gen_01_delta_364_prev = 0;
    }
    
    number gen_01_latch_368_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_368_value = x;
        }
    
        return this->gen_01_latch_368_value;
    }
    
    void gen_01_latch_368_dspsetup() {
        this->gen_01_latch_368_reset();
    }
    
    void gen_01_latch_368_init() {
        this->gen_01_latch_368_reset();
    }
    
    void gen_01_latch_368_reset() {
        this->gen_01_latch_368_value = 0;
    }
    
    number gen_01_latch_370_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_370_value = x;
        }
    
        return this->gen_01_latch_370_value;
    }
    
    void gen_01_latch_370_dspsetup() {
        this->gen_01_latch_370_reset();
    }
    
    void gen_01_latch_370_init() {
        this->gen_01_latch_370_reset();
    }
    
    void gen_01_latch_370_reset() {
        this->gen_01_latch_370_value = 0;
    }
    
    array<number, 3> gen_01_counter_378_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_378_count = 0;
            this->gen_01_counter_378_carry = 0;
        } else {
            this->gen_01_counter_378_count += a;
        }
    
        return {this->gen_01_counter_378_count, carry_flag, this->gen_01_counter_378_carry};
    }
    
    void gen_01_counter_378_init() {
        this->gen_01_counter_378_count = 0;
    }
    
    void gen_01_counter_378_reset() {
        this->gen_01_counter_378_carry = 0;
        this->gen_01_counter_378_count = 0;
    }
    
    void gen_01_noise_390_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_390_state
        );
    }
    
    void gen_01_noise_390_init() {
        this->gen_01_noise_390_reset();
    }
    
    void gen_01_noise_390_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_390_state);
    }
    
    number gen_01_noise_390_next() {
        return xoshiro_next(this->gen_01_noise_390_state);
    }
    
    void gen_01_noise_392_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_392_state
        );
    }
    
    void gen_01_noise_392_init() {
        this->gen_01_noise_392_reset();
    }
    
    void gen_01_noise_392_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_392_state);
    }
    
    number gen_01_noise_392_next() {
        return xoshiro_next(this->gen_01_noise_392_state);
    }
    
    number gen_01_slide_396_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_396_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_396_prev = this->gen_01_slide_396_prev + ((x > this->gen_01_slide_396_prev ? iup : idown)) * temp;
        return this->gen_01_slide_396_prev;
    }
    
    void gen_01_slide_396_reset() {
        this->gen_01_slide_396_prev = 0;
    }
    
    number gen_01_slide_406_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_406_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_406_prev = this->gen_01_slide_406_prev + ((x > this->gen_01_slide_406_prev ? iup : idown)) * temp;
        return this->gen_01_slide_406_prev;
    }
    
    void gen_01_slide_406_reset() {
        this->gen_01_slide_406_prev = 0;
    }
    
    number gen_01_latch_409_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_409_value = x;
        }
    
        return this->gen_01_latch_409_value;
    }
    
    void gen_01_latch_409_dspsetup() {
        this->gen_01_latch_409_reset();
    }
    
    void gen_01_latch_409_init() {
        this->gen_01_latch_409_reset();
    }
    
    void gen_01_latch_409_reset() {
        this->gen_01_latch_409_value = 0;
    }
    
    number gen_01_slide_412_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_412_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_412_prev = this->gen_01_slide_412_prev + ((x > this->gen_01_slide_412_prev ? iup : idown)) * temp;
        return this->gen_01_slide_412_prev;
    }
    
    void gen_01_slide_412_reset() {
        this->gen_01_slide_412_prev = 0;
    }
    
    number gen_01_slide_417_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_417_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_417_prev = this->gen_01_slide_417_prev + ((x > this->gen_01_slide_417_prev ? iup : idown)) * temp;
        return this->gen_01_slide_417_prev;
    }
    
    void gen_01_slide_417_reset() {
        this->gen_01_slide_417_prev = 0;
    }
    
    number gen_01_latch_423_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_423_value = x;
        }
    
        return this->gen_01_latch_423_value;
    }
    
    void gen_01_latch_423_dspsetup() {
        this->gen_01_latch_423_reset();
    }
    
    void gen_01_latch_423_init() {
        this->gen_01_latch_423_reset();
    }
    
    void gen_01_latch_423_reset() {
        this->gen_01_latch_423_value = 0;
    }
    
    number gen_01_slide_441_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_441_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_441_prev = this->gen_01_slide_441_prev + ((x > this->gen_01_slide_441_prev ? iup : idown)) * temp;
        return this->gen_01_slide_441_prev;
    }
    
    void gen_01_slide_441_reset() {
        this->gen_01_slide_441_prev = 0;
    }
    
    void gen_01_noise_443_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_443_state
        );
    }
    
    void gen_01_noise_443_init() {
        this->gen_01_noise_443_reset();
    }
    
    void gen_01_noise_443_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_443_state);
    }
    
    number gen_01_noise_443_next() {
        return xoshiro_next(this->gen_01_noise_443_state);
    }
    
    number gen_01_slide_452_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_452_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_452_prev = this->gen_01_slide_452_prev + ((x > this->gen_01_slide_452_prev ? iup : idown)) * temp;
        return this->gen_01_slide_452_prev;
    }
    
    void gen_01_slide_452_reset() {
        this->gen_01_slide_452_prev = 0;
    }
    
    number gen_01_phasor_454_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_454_conv;
    
        if (this->gen_01_phasor_454_currentPhase < 0.)
            this->gen_01_phasor_454_currentPhase = 1. + this->gen_01_phasor_454_currentPhase;
    
        if (this->gen_01_phasor_454_currentPhase > 1.)
            this->gen_01_phasor_454_currentPhase = this->gen_01_phasor_454_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_454_currentPhase;
        this->gen_01_phasor_454_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_454_reset() {
        this->gen_01_phasor_454_currentPhase = 0;
    }
    
    void gen_01_phasor_454_dspsetup() {
        this->gen_01_phasor_454_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_456_next(number x) {
        number temp = (number)(x - this->gen_01_delta_456_prev);
        this->gen_01_delta_456_prev = x;
        return temp;
    }
    
    void gen_01_delta_456_dspsetup() {
        this->gen_01_delta_456_reset();
    }
    
    void gen_01_delta_456_reset() {
        this->gen_01_delta_456_prev = 0;
    }
    
    array<number, 3> gen_01_counter_459_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_459_count = 0;
            this->gen_01_counter_459_carry = 0;
        } else {
            this->gen_01_counter_459_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_459_count >= limit) || (a < 0 && this->gen_01_counter_459_count <= limit)) {
                    this->gen_01_counter_459_count = 0;
                    this->gen_01_counter_459_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_459_count, carry_flag, this->gen_01_counter_459_carry};
    }
    
    void gen_01_counter_459_init() {
        this->gen_01_counter_459_count = 0;
    }
    
    void gen_01_counter_459_reset() {
        this->gen_01_counter_459_carry = 0;
        this->gen_01_counter_459_count = 0;
    }
    
    number gen_01_delta_462_next(number x) {
        number temp = (number)(x - this->gen_01_delta_462_prev);
        this->gen_01_delta_462_prev = x;
        return temp;
    }
    
    void gen_01_delta_462_dspsetup() {
        this->gen_01_delta_462_reset();
    }
    
    void gen_01_delta_462_reset() {
        this->gen_01_delta_462_prev = 0;
    }
    
    number gen_01_latch_466_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_466_value = x;
        }
    
        return this->gen_01_latch_466_value;
    }
    
    void gen_01_latch_466_dspsetup() {
        this->gen_01_latch_466_reset();
    }
    
    void gen_01_latch_466_init() {
        this->gen_01_latch_466_reset();
    }
    
    void gen_01_latch_466_reset() {
        this->gen_01_latch_466_value = 0;
    }
    
    number gen_01_latch_469_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_469_value = x;
        }
    
        return this->gen_01_latch_469_value;
    }
    
    void gen_01_latch_469_dspsetup() {
        this->gen_01_latch_469_reset();
    }
    
    void gen_01_latch_469_init() {
        this->gen_01_latch_469_reset();
    }
    
    void gen_01_latch_469_reset() {
        this->gen_01_latch_469_value = 0;
    }
    
    array<number, 3> gen_01_counter_477_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_477_count = 0;
            this->gen_01_counter_477_carry = 0;
        } else {
            this->gen_01_counter_477_count += a;
        }
    
        return {this->gen_01_counter_477_count, carry_flag, this->gen_01_counter_477_carry};
    }
    
    void gen_01_counter_477_init() {
        this->gen_01_counter_477_count = 0;
    }
    
    void gen_01_counter_477_reset() {
        this->gen_01_counter_477_carry = 0;
        this->gen_01_counter_477_count = 0;
    }
    
    void gen_01_noise_486_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_486_state
        );
    }
    
    void gen_01_noise_486_init() {
        this->gen_01_noise_486_reset();
    }
    
    void gen_01_noise_486_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_486_state);
    }
    
    number gen_01_noise_486_next() {
        return xoshiro_next(this->gen_01_noise_486_state);
    }
    
    void gen_01_noise_488_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_488_state
        );
    }
    
    void gen_01_noise_488_init() {
        this->gen_01_noise_488_reset();
    }
    
    void gen_01_noise_488_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_488_state);
    }
    
    number gen_01_noise_488_next() {
        return xoshiro_next(this->gen_01_noise_488_state);
    }
    
    number gen_01_slide_492_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_492_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_492_prev = this->gen_01_slide_492_prev + ((x > this->gen_01_slide_492_prev ? iup : idown)) * temp;
        return this->gen_01_slide_492_prev;
    }
    
    void gen_01_slide_492_reset() {
        this->gen_01_slide_492_prev = 0;
    }
    
    number gen_01_slide_502_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_502_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_502_prev = this->gen_01_slide_502_prev + ((x > this->gen_01_slide_502_prev ? iup : idown)) * temp;
        return this->gen_01_slide_502_prev;
    }
    
    void gen_01_slide_502_reset() {
        this->gen_01_slide_502_prev = 0;
    }
    
    number gen_01_latch_505_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_505_value = x;
        }
    
        return this->gen_01_latch_505_value;
    }
    
    void gen_01_latch_505_dspsetup() {
        this->gen_01_latch_505_reset();
    }
    
    void gen_01_latch_505_init() {
        this->gen_01_latch_505_reset();
    }
    
    void gen_01_latch_505_reset() {
        this->gen_01_latch_505_value = 0;
    }
    
    number gen_01_slide_508_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_508_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_508_prev = this->gen_01_slide_508_prev + ((x > this->gen_01_slide_508_prev ? iup : idown)) * temp;
        return this->gen_01_slide_508_prev;
    }
    
    void gen_01_slide_508_reset() {
        this->gen_01_slide_508_prev = 0;
    }
    
    number gen_01_slide_513_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_513_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_513_prev = this->gen_01_slide_513_prev + ((x > this->gen_01_slide_513_prev ? iup : idown)) * temp;
        return this->gen_01_slide_513_prev;
    }
    
    void gen_01_slide_513_reset() {
        this->gen_01_slide_513_prev = 0;
    }
    
    number gen_01_latch_519_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_519_value = x;
        }
    
        return this->gen_01_latch_519_value;
    }
    
    void gen_01_latch_519_dspsetup() {
        this->gen_01_latch_519_reset();
    }
    
    void gen_01_latch_519_init() {
        this->gen_01_latch_519_reset();
    }
    
    void gen_01_latch_519_reset() {
        this->gen_01_latch_519_value = 0;
    }
    
    number gen_01_slide_537_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_537_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_537_prev = this->gen_01_slide_537_prev + ((x > this->gen_01_slide_537_prev ? iup : idown)) * temp;
        return this->gen_01_slide_537_prev;
    }
    
    void gen_01_slide_537_reset() {
        this->gen_01_slide_537_prev = 0;
    }
    
    void gen_01_noise_539_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_539_state
        );
    }
    
    void gen_01_noise_539_init() {
        this->gen_01_noise_539_reset();
    }
    
    void gen_01_noise_539_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_539_state);
    }
    
    number gen_01_noise_539_next() {
        return xoshiro_next(this->gen_01_noise_539_state);
    }
    
    number gen_01_slide_549_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_549_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_549_prev = this->gen_01_slide_549_prev + ((x > this->gen_01_slide_549_prev ? iup : idown)) * temp;
        return this->gen_01_slide_549_prev;
    }
    
    void gen_01_slide_549_reset() {
        this->gen_01_slide_549_prev = 0;
    }
    
    number gen_01_phasor_551_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_551_conv;
    
        if (this->gen_01_phasor_551_currentPhase < 0.)
            this->gen_01_phasor_551_currentPhase = 1. + this->gen_01_phasor_551_currentPhase;
    
        if (this->gen_01_phasor_551_currentPhase > 1.)
            this->gen_01_phasor_551_currentPhase = this->gen_01_phasor_551_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_551_currentPhase;
        this->gen_01_phasor_551_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_551_reset() {
        this->gen_01_phasor_551_currentPhase = 0;
    }
    
    void gen_01_phasor_551_dspsetup() {
        this->gen_01_phasor_551_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_553_next(number x) {
        number temp = (number)(x - this->gen_01_delta_553_prev);
        this->gen_01_delta_553_prev = x;
        return temp;
    }
    
    void gen_01_delta_553_dspsetup() {
        this->gen_01_delta_553_reset();
    }
    
    void gen_01_delta_553_reset() {
        this->gen_01_delta_553_prev = 0;
    }
    
    array<number, 3> gen_01_counter_556_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_556_count = 0;
            this->gen_01_counter_556_carry = 0;
        } else {
            this->gen_01_counter_556_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_556_count >= limit) || (a < 0 && this->gen_01_counter_556_count <= limit)) {
                    this->gen_01_counter_556_count = 0;
                    this->gen_01_counter_556_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_556_count, carry_flag, this->gen_01_counter_556_carry};
    }
    
    void gen_01_counter_556_init() {
        this->gen_01_counter_556_count = 0;
    }
    
    void gen_01_counter_556_reset() {
        this->gen_01_counter_556_carry = 0;
        this->gen_01_counter_556_count = 0;
    }
    
    number gen_01_delta_559_next(number x) {
        number temp = (number)(x - this->gen_01_delta_559_prev);
        this->gen_01_delta_559_prev = x;
        return temp;
    }
    
    void gen_01_delta_559_dspsetup() {
        this->gen_01_delta_559_reset();
    }
    
    void gen_01_delta_559_reset() {
        this->gen_01_delta_559_prev = 0;
    }
    
    number gen_01_latch_563_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_563_value = x;
        }
    
        return this->gen_01_latch_563_value;
    }
    
    void gen_01_latch_563_dspsetup() {
        this->gen_01_latch_563_reset();
    }
    
    void gen_01_latch_563_init() {
        this->gen_01_latch_563_reset();
    }
    
    void gen_01_latch_563_reset() {
        this->gen_01_latch_563_value = 0;
    }
    
    number gen_01_latch_571_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_571_value = x;
        }
    
        return this->gen_01_latch_571_value;
    }
    
    void gen_01_latch_571_dspsetup() {
        this->gen_01_latch_571_reset();
    }
    
    void gen_01_latch_571_init() {
        this->gen_01_latch_571_reset();
    }
    
    void gen_01_latch_571_reset() {
        this->gen_01_latch_571_value = 0;
    }
    
    array<number, 3> gen_01_counter_573_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_573_count = 0;
            this->gen_01_counter_573_carry = 0;
        } else {
            this->gen_01_counter_573_count += a;
        }
    
        return {this->gen_01_counter_573_count, carry_flag, this->gen_01_counter_573_carry};
    }
    
    void gen_01_counter_573_init() {
        this->gen_01_counter_573_count = 0;
    }
    
    void gen_01_counter_573_reset() {
        this->gen_01_counter_573_carry = 0;
        this->gen_01_counter_573_count = 0;
    }
    
    void gen_01_noise_582_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_582_state
        );
    }
    
    void gen_01_noise_582_init() {
        this->gen_01_noise_582_reset();
    }
    
    void gen_01_noise_582_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_582_state);
    }
    
    number gen_01_noise_582_next() {
        return xoshiro_next(this->gen_01_noise_582_state);
    }
    
    void gen_01_noise_584_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_584_state
        );
    }
    
    void gen_01_noise_584_init() {
        this->gen_01_noise_584_reset();
    }
    
    void gen_01_noise_584_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_584_state);
    }
    
    number gen_01_noise_584_next() {
        return xoshiro_next(this->gen_01_noise_584_state);
    }
    
    number gen_01_slide_588_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_588_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_588_prev = this->gen_01_slide_588_prev + ((x > this->gen_01_slide_588_prev ? iup : idown)) * temp;
        return this->gen_01_slide_588_prev;
    }
    
    void gen_01_slide_588_reset() {
        this->gen_01_slide_588_prev = 0;
    }
    
    number gen_01_slide_598_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_598_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_598_prev = this->gen_01_slide_598_prev + ((x > this->gen_01_slide_598_prev ? iup : idown)) * temp;
        return this->gen_01_slide_598_prev;
    }
    
    void gen_01_slide_598_reset() {
        this->gen_01_slide_598_prev = 0;
    }
    
    number gen_01_latch_601_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_601_value = x;
        }
    
        return this->gen_01_latch_601_value;
    }
    
    void gen_01_latch_601_dspsetup() {
        this->gen_01_latch_601_reset();
    }
    
    void gen_01_latch_601_init() {
        this->gen_01_latch_601_reset();
    }
    
    void gen_01_latch_601_reset() {
        this->gen_01_latch_601_value = 0;
    }
    
    number gen_01_slide_604_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_604_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_604_prev = this->gen_01_slide_604_prev + ((x > this->gen_01_slide_604_prev ? iup : idown)) * temp;
        return this->gen_01_slide_604_prev;
    }
    
    void gen_01_slide_604_reset() {
        this->gen_01_slide_604_prev = 0;
    }
    
    number gen_01_slide_609_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_609_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_609_prev = this->gen_01_slide_609_prev + ((x > this->gen_01_slide_609_prev ? iup : idown)) * temp;
        return this->gen_01_slide_609_prev;
    }
    
    void gen_01_slide_609_reset() {
        this->gen_01_slide_609_prev = 0;
    }
    
    number gen_01_latch_615_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_615_value = x;
        }
    
        return this->gen_01_latch_615_value;
    }
    
    void gen_01_latch_615_dspsetup() {
        this->gen_01_latch_615_reset();
    }
    
    void gen_01_latch_615_init() {
        this->gen_01_latch_615_reset();
    }
    
    void gen_01_latch_615_reset() {
        this->gen_01_latch_615_value = 0;
    }
    
    number gen_01_slide_633_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_633_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_633_prev = this->gen_01_slide_633_prev + ((x > this->gen_01_slide_633_prev ? iup : idown)) * temp;
        return this->gen_01_slide_633_prev;
    }
    
    void gen_01_slide_633_reset() {
        this->gen_01_slide_633_prev = 0;
    }
    
    void gen_01_noise_635_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_635_state
        );
    }
    
    void gen_01_noise_635_init() {
        this->gen_01_noise_635_reset();
    }
    
    void gen_01_noise_635_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_635_state);
    }
    
    number gen_01_noise_635_next() {
        return xoshiro_next(this->gen_01_noise_635_state);
    }
    
    number gen_01_slide_641_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_641_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_641_prev = this->gen_01_slide_641_prev + ((x > this->gen_01_slide_641_prev ? iup : idown)) * temp;
        return this->gen_01_slide_641_prev;
    }
    
    void gen_01_slide_641_reset() {
        this->gen_01_slide_641_prev = 0;
    }
    
    number gen_01_phasor_643_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_643_conv;
    
        if (this->gen_01_phasor_643_currentPhase < 0.)
            this->gen_01_phasor_643_currentPhase = 1. + this->gen_01_phasor_643_currentPhase;
    
        if (this->gen_01_phasor_643_currentPhase > 1.)
            this->gen_01_phasor_643_currentPhase = this->gen_01_phasor_643_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_643_currentPhase;
        this->gen_01_phasor_643_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_643_reset() {
        this->gen_01_phasor_643_currentPhase = 0;
    }
    
    void gen_01_phasor_643_dspsetup() {
        this->gen_01_phasor_643_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_645_next(number x) {
        number temp = (number)(x - this->gen_01_delta_645_prev);
        this->gen_01_delta_645_prev = x;
        return temp;
    }
    
    void gen_01_delta_645_dspsetup() {
        this->gen_01_delta_645_reset();
    }
    
    void gen_01_delta_645_reset() {
        this->gen_01_delta_645_prev = 0;
    }
    
    array<number, 3> gen_01_counter_648_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_648_count = 0;
            this->gen_01_counter_648_carry = 0;
        } else {
            this->gen_01_counter_648_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_648_count >= limit) || (a < 0 && this->gen_01_counter_648_count <= limit)) {
                    this->gen_01_counter_648_count = 0;
                    this->gen_01_counter_648_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_648_count, carry_flag, this->gen_01_counter_648_carry};
    }
    
    void gen_01_counter_648_init() {
        this->gen_01_counter_648_count = 0;
    }
    
    void gen_01_counter_648_reset() {
        this->gen_01_counter_648_carry = 0;
        this->gen_01_counter_648_count = 0;
    }
    
    number gen_01_delta_651_next(number x) {
        number temp = (number)(x - this->gen_01_delta_651_prev);
        this->gen_01_delta_651_prev = x;
        return temp;
    }
    
    void gen_01_delta_651_dspsetup() {
        this->gen_01_delta_651_reset();
    }
    
    void gen_01_delta_651_reset() {
        this->gen_01_delta_651_prev = 0;
    }
    
    number gen_01_latch_655_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_655_value = x;
        }
    
        return this->gen_01_latch_655_value;
    }
    
    void gen_01_latch_655_dspsetup() {
        this->gen_01_latch_655_reset();
    }
    
    void gen_01_latch_655_init() {
        this->gen_01_latch_655_reset();
    }
    
    void gen_01_latch_655_reset() {
        this->gen_01_latch_655_value = 0;
    }
    
    number gen_01_latch_657_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_657_value = x;
        }
    
        return this->gen_01_latch_657_value;
    }
    
    void gen_01_latch_657_dspsetup() {
        this->gen_01_latch_657_reset();
    }
    
    void gen_01_latch_657_init() {
        this->gen_01_latch_657_reset();
    }
    
    void gen_01_latch_657_reset() {
        this->gen_01_latch_657_value = 0;
    }
    
    array<number, 3> gen_01_counter_665_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_665_count = 0;
            this->gen_01_counter_665_carry = 0;
        } else {
            this->gen_01_counter_665_count += a;
        }
    
        return {this->gen_01_counter_665_count, carry_flag, this->gen_01_counter_665_carry};
    }
    
    void gen_01_counter_665_init() {
        this->gen_01_counter_665_count = 0;
    }
    
    void gen_01_counter_665_reset() {
        this->gen_01_counter_665_carry = 0;
        this->gen_01_counter_665_count = 0;
    }
    
    void gen_01_noise_677_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_677_state
        );
    }
    
    void gen_01_noise_677_init() {
        this->gen_01_noise_677_reset();
    }
    
    void gen_01_noise_677_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_677_state);
    }
    
    number gen_01_noise_677_next() {
        return xoshiro_next(this->gen_01_noise_677_state);
    }
    
    void gen_01_noise_679_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_679_state
        );
    }
    
    void gen_01_noise_679_init() {
        this->gen_01_noise_679_reset();
    }
    
    void gen_01_noise_679_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_679_state);
    }
    
    number gen_01_noise_679_next() {
        return xoshiro_next(this->gen_01_noise_679_state);
    }
    
    number gen_01_slide_683_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_683_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_683_prev = this->gen_01_slide_683_prev + ((x > this->gen_01_slide_683_prev ? iup : idown)) * temp;
        return this->gen_01_slide_683_prev;
    }
    
    void gen_01_slide_683_reset() {
        this->gen_01_slide_683_prev = 0;
    }
    
    number gen_01_slide_693_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_693_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_693_prev = this->gen_01_slide_693_prev + ((x > this->gen_01_slide_693_prev ? iup : idown)) * temp;
        return this->gen_01_slide_693_prev;
    }
    
    void gen_01_slide_693_reset() {
        this->gen_01_slide_693_prev = 0;
    }
    
    number gen_01_latch_696_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_696_value = x;
        }
    
        return this->gen_01_latch_696_value;
    }
    
    void gen_01_latch_696_dspsetup() {
        this->gen_01_latch_696_reset();
    }
    
    void gen_01_latch_696_init() {
        this->gen_01_latch_696_reset();
    }
    
    void gen_01_latch_696_reset() {
        this->gen_01_latch_696_value = 0;
    }
    
    number gen_01_slide_699_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_699_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_699_prev = this->gen_01_slide_699_prev + ((x > this->gen_01_slide_699_prev ? iup : idown)) * temp;
        return this->gen_01_slide_699_prev;
    }
    
    void gen_01_slide_699_reset() {
        this->gen_01_slide_699_prev = 0;
    }
    
    number gen_01_slide_704_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_704_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_704_prev = this->gen_01_slide_704_prev + ((x > this->gen_01_slide_704_prev ? iup : idown)) * temp;
        return this->gen_01_slide_704_prev;
    }
    
    void gen_01_slide_704_reset() {
        this->gen_01_slide_704_prev = 0;
    }
    
    number gen_01_latch_710_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_710_value = x;
        }
    
        return this->gen_01_latch_710_value;
    }
    
    void gen_01_latch_710_dspsetup() {
        this->gen_01_latch_710_reset();
    }
    
    void gen_01_latch_710_init() {
        this->gen_01_latch_710_reset();
    }
    
    void gen_01_latch_710_reset() {
        this->gen_01_latch_710_value = 0;
    }
    
    number gen_01_slide_728_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_728_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_728_prev = this->gen_01_slide_728_prev + ((x > this->gen_01_slide_728_prev ? iup : idown)) * temp;
        return this->gen_01_slide_728_prev;
    }
    
    void gen_01_slide_728_reset() {
        this->gen_01_slide_728_prev = 0;
    }
    
    void gen_01_noise_730_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_730_state
        );
    }
    
    void gen_01_noise_730_init() {
        this->gen_01_noise_730_reset();
    }
    
    void gen_01_noise_730_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_730_state);
    }
    
    number gen_01_noise_730_next() {
        return xoshiro_next(this->gen_01_noise_730_state);
    }
    
    number gen_01_slide_739_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_739_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_739_prev = this->gen_01_slide_739_prev + ((x > this->gen_01_slide_739_prev ? iup : idown)) * temp;
        return this->gen_01_slide_739_prev;
    }
    
    void gen_01_slide_739_reset() {
        this->gen_01_slide_739_prev = 0;
    }
    
    number gen_01_phasor_741_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_741_conv;
    
        if (this->gen_01_phasor_741_currentPhase < 0.)
            this->gen_01_phasor_741_currentPhase = 1. + this->gen_01_phasor_741_currentPhase;
    
        if (this->gen_01_phasor_741_currentPhase > 1.)
            this->gen_01_phasor_741_currentPhase = this->gen_01_phasor_741_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_741_currentPhase;
        this->gen_01_phasor_741_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_741_reset() {
        this->gen_01_phasor_741_currentPhase = 0;
    }
    
    void gen_01_phasor_741_dspsetup() {
        this->gen_01_phasor_741_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_743_next(number x) {
        number temp = (number)(x - this->gen_01_delta_743_prev);
        this->gen_01_delta_743_prev = x;
        return temp;
    }
    
    void gen_01_delta_743_dspsetup() {
        this->gen_01_delta_743_reset();
    }
    
    void gen_01_delta_743_reset() {
        this->gen_01_delta_743_prev = 0;
    }
    
    array<number, 3> gen_01_counter_746_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_746_count = 0;
            this->gen_01_counter_746_carry = 0;
        } else {
            this->gen_01_counter_746_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_746_count >= limit) || (a < 0 && this->gen_01_counter_746_count <= limit)) {
                    this->gen_01_counter_746_count = 0;
                    this->gen_01_counter_746_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_746_count, carry_flag, this->gen_01_counter_746_carry};
    }
    
    void gen_01_counter_746_init() {
        this->gen_01_counter_746_count = 0;
    }
    
    void gen_01_counter_746_reset() {
        this->gen_01_counter_746_carry = 0;
        this->gen_01_counter_746_count = 0;
    }
    
    number gen_01_delta_749_next(number x) {
        number temp = (number)(x - this->gen_01_delta_749_prev);
        this->gen_01_delta_749_prev = x;
        return temp;
    }
    
    void gen_01_delta_749_dspsetup() {
        this->gen_01_delta_749_reset();
    }
    
    void gen_01_delta_749_reset() {
        this->gen_01_delta_749_prev = 0;
    }
    
    number gen_01_latch_753_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_753_value = x;
        }
    
        return this->gen_01_latch_753_value;
    }
    
    void gen_01_latch_753_dspsetup() {
        this->gen_01_latch_753_reset();
    }
    
    void gen_01_latch_753_init() {
        this->gen_01_latch_753_reset();
    }
    
    void gen_01_latch_753_reset() {
        this->gen_01_latch_753_value = 0;
    }
    
    number gen_01_latch_755_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_755_value = x;
        }
    
        return this->gen_01_latch_755_value;
    }
    
    void gen_01_latch_755_dspsetup() {
        this->gen_01_latch_755_reset();
    }
    
    void gen_01_latch_755_init() {
        this->gen_01_latch_755_reset();
    }
    
    void gen_01_latch_755_reset() {
        this->gen_01_latch_755_value = 0;
    }
    
    array<number, 3> gen_01_counter_763_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_763_count = 0;
            this->gen_01_counter_763_carry = 0;
        } else {
            this->gen_01_counter_763_count += a;
        }
    
        return {this->gen_01_counter_763_count, carry_flag, this->gen_01_counter_763_carry};
    }
    
    void gen_01_counter_763_init() {
        this->gen_01_counter_763_count = 0;
    }
    
    void gen_01_counter_763_reset() {
        this->gen_01_counter_763_carry = 0;
        this->gen_01_counter_763_count = 0;
    }
    
    void gen_01_noise_772_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_772_state
        );
    }
    
    void gen_01_noise_772_init() {
        this->gen_01_noise_772_reset();
    }
    
    void gen_01_noise_772_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_772_state);
    }
    
    number gen_01_noise_772_next() {
        return xoshiro_next(this->gen_01_noise_772_state);
    }
    
    void gen_01_noise_774_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_774_state
        );
    }
    
    void gen_01_noise_774_init() {
        this->gen_01_noise_774_reset();
    }
    
    void gen_01_noise_774_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_774_state);
    }
    
    number gen_01_noise_774_next() {
        return xoshiro_next(this->gen_01_noise_774_state);
    }
    
    number gen_01_slide_778_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_778_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_778_prev = this->gen_01_slide_778_prev + ((x > this->gen_01_slide_778_prev ? iup : idown)) * temp;
        return this->gen_01_slide_778_prev;
    }
    
    void gen_01_slide_778_reset() {
        this->gen_01_slide_778_prev = 0;
    }
    
    number gen_01_slide_788_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_788_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_788_prev = this->gen_01_slide_788_prev + ((x > this->gen_01_slide_788_prev ? iup : idown)) * temp;
        return this->gen_01_slide_788_prev;
    }
    
    void gen_01_slide_788_reset() {
        this->gen_01_slide_788_prev = 0;
    }
    
    number gen_01_latch_791_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_791_value = x;
        }
    
        return this->gen_01_latch_791_value;
    }
    
    void gen_01_latch_791_dspsetup() {
        this->gen_01_latch_791_reset();
    }
    
    void gen_01_latch_791_init() {
        this->gen_01_latch_791_reset();
    }
    
    void gen_01_latch_791_reset() {
        this->gen_01_latch_791_value = 0;
    }
    
    number gen_01_slide_795_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_795_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_795_prev = this->gen_01_slide_795_prev + ((x > this->gen_01_slide_795_prev ? iup : idown)) * temp;
        return this->gen_01_slide_795_prev;
    }
    
    void gen_01_slide_795_reset() {
        this->gen_01_slide_795_prev = 0;
    }
    
    number gen_01_slide_800_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_800_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_800_prev = this->gen_01_slide_800_prev + ((x > this->gen_01_slide_800_prev ? iup : idown)) * temp;
        return this->gen_01_slide_800_prev;
    }
    
    void gen_01_slide_800_reset() {
        this->gen_01_slide_800_prev = 0;
    }
    
    number gen_01_latch_806_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_806_value = x;
        }
    
        return this->gen_01_latch_806_value;
    }
    
    void gen_01_latch_806_dspsetup() {
        this->gen_01_latch_806_reset();
    }
    
    void gen_01_latch_806_init() {
        this->gen_01_latch_806_reset();
    }
    
    void gen_01_latch_806_reset() {
        this->gen_01_latch_806_value = 0;
    }
    
    number gen_01_slide_824_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_824_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_824_prev = this->gen_01_slide_824_prev + ((x > this->gen_01_slide_824_prev ? iup : idown)) * temp;
        return this->gen_01_slide_824_prev;
    }
    
    void gen_01_slide_824_reset() {
        this->gen_01_slide_824_prev = 0;
    }
    
    void gen_01_noise_827_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_827_state
        );
    }
    
    void gen_01_noise_827_init() {
        this->gen_01_noise_827_reset();
    }
    
    void gen_01_noise_827_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_827_state);
    }
    
    number gen_01_noise_827_next() {
        return xoshiro_next(this->gen_01_noise_827_state);
    }
    
    number gen_01_slide_836_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_836_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_836_prev = this->gen_01_slide_836_prev + ((x > this->gen_01_slide_836_prev ? iup : idown)) * temp;
        return this->gen_01_slide_836_prev;
    }
    
    void gen_01_slide_836_reset() {
        this->gen_01_slide_836_prev = 0;
    }
    
    number gen_01_phasor_838_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_838_conv;
    
        if (this->gen_01_phasor_838_currentPhase < 0.)
            this->gen_01_phasor_838_currentPhase = 1. + this->gen_01_phasor_838_currentPhase;
    
        if (this->gen_01_phasor_838_currentPhase > 1.)
            this->gen_01_phasor_838_currentPhase = this->gen_01_phasor_838_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_838_currentPhase;
        this->gen_01_phasor_838_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_838_reset() {
        this->gen_01_phasor_838_currentPhase = 0;
    }
    
    void gen_01_phasor_838_dspsetup() {
        this->gen_01_phasor_838_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_840_next(number x) {
        number temp = (number)(x - this->gen_01_delta_840_prev);
        this->gen_01_delta_840_prev = x;
        return temp;
    }
    
    void gen_01_delta_840_dspsetup() {
        this->gen_01_delta_840_reset();
    }
    
    void gen_01_delta_840_reset() {
        this->gen_01_delta_840_prev = 0;
    }
    
    array<number, 3> gen_01_counter_843_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_843_count = 0;
            this->gen_01_counter_843_carry = 0;
        } else {
            this->gen_01_counter_843_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_843_count >= limit) || (a < 0 && this->gen_01_counter_843_count <= limit)) {
                    this->gen_01_counter_843_count = 0;
                    this->gen_01_counter_843_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_843_count, carry_flag, this->gen_01_counter_843_carry};
    }
    
    void gen_01_counter_843_init() {
        this->gen_01_counter_843_count = 0;
    }
    
    void gen_01_counter_843_reset() {
        this->gen_01_counter_843_carry = 0;
        this->gen_01_counter_843_count = 0;
    }
    
    number gen_01_delta_846_next(number x) {
        number temp = (number)(x - this->gen_01_delta_846_prev);
        this->gen_01_delta_846_prev = x;
        return temp;
    }
    
    void gen_01_delta_846_dspsetup() {
        this->gen_01_delta_846_reset();
    }
    
    void gen_01_delta_846_reset() {
        this->gen_01_delta_846_prev = 0;
    }
    
    number gen_01_latch_850_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_850_value = x;
        }
    
        return this->gen_01_latch_850_value;
    }
    
    void gen_01_latch_850_dspsetup() {
        this->gen_01_latch_850_reset();
    }
    
    void gen_01_latch_850_init() {
        this->gen_01_latch_850_reset();
    }
    
    void gen_01_latch_850_reset() {
        this->gen_01_latch_850_value = 0;
    }
    
    number gen_01_latch_852_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_852_value = x;
        }
    
        return this->gen_01_latch_852_value;
    }
    
    void gen_01_latch_852_dspsetup() {
        this->gen_01_latch_852_reset();
    }
    
    void gen_01_latch_852_init() {
        this->gen_01_latch_852_reset();
    }
    
    void gen_01_latch_852_reset() {
        this->gen_01_latch_852_value = 0;
    }
    
    array<number, 3> gen_01_counter_860_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_860_count = 0;
            this->gen_01_counter_860_carry = 0;
        } else {
            this->gen_01_counter_860_count += a;
        }
    
        return {this->gen_01_counter_860_count, carry_flag, this->gen_01_counter_860_carry};
    }
    
    void gen_01_counter_860_init() {
        this->gen_01_counter_860_count = 0;
    }
    
    void gen_01_counter_860_reset() {
        this->gen_01_counter_860_carry = 0;
        this->gen_01_counter_860_count = 0;
    }
    
    void gen_01_noise_869_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_869_state
        );
    }
    
    void gen_01_noise_869_init() {
        this->gen_01_noise_869_reset();
    }
    
    void gen_01_noise_869_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_869_state);
    }
    
    number gen_01_noise_869_next() {
        return xoshiro_next(this->gen_01_noise_869_state);
    }
    
    void gen_01_noise_871_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_871_state
        );
    }
    
    void gen_01_noise_871_init() {
        this->gen_01_noise_871_reset();
    }
    
    void gen_01_noise_871_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_871_state);
    }
    
    number gen_01_noise_871_next() {
        return xoshiro_next(this->gen_01_noise_871_state);
    }
    
    number gen_01_slide_875_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_875_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_875_prev = this->gen_01_slide_875_prev + ((x > this->gen_01_slide_875_prev ? iup : idown)) * temp;
        return this->gen_01_slide_875_prev;
    }
    
    void gen_01_slide_875_reset() {
        this->gen_01_slide_875_prev = 0;
    }
    
    number gen_01_slide_885_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_885_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_885_prev = this->gen_01_slide_885_prev + ((x > this->gen_01_slide_885_prev ? iup : idown)) * temp;
        return this->gen_01_slide_885_prev;
    }
    
    void gen_01_slide_885_reset() {
        this->gen_01_slide_885_prev = 0;
    }
    
    number gen_01_latch_888_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_888_value = x;
        }
    
        return this->gen_01_latch_888_value;
    }
    
    void gen_01_latch_888_dspsetup() {
        this->gen_01_latch_888_reset();
    }
    
    void gen_01_latch_888_init() {
        this->gen_01_latch_888_reset();
    }
    
    void gen_01_latch_888_reset() {
        this->gen_01_latch_888_value = 0;
    }
    
    number gen_01_slide_891_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_891_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_891_prev = this->gen_01_slide_891_prev + ((x > this->gen_01_slide_891_prev ? iup : idown)) * temp;
        return this->gen_01_slide_891_prev;
    }
    
    void gen_01_slide_891_reset() {
        this->gen_01_slide_891_prev = 0;
    }
    
    number gen_01_slide_896_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_896_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_896_prev = this->gen_01_slide_896_prev + ((x > this->gen_01_slide_896_prev ? iup : idown)) * temp;
        return this->gen_01_slide_896_prev;
    }
    
    void gen_01_slide_896_reset() {
        this->gen_01_slide_896_prev = 0;
    }
    
    number gen_01_latch_902_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_902_value = x;
        }
    
        return this->gen_01_latch_902_value;
    }
    
    void gen_01_latch_902_dspsetup() {
        this->gen_01_latch_902_reset();
    }
    
    void gen_01_latch_902_init() {
        this->gen_01_latch_902_reset();
    }
    
    void gen_01_latch_902_reset() {
        this->gen_01_latch_902_value = 0;
    }
    
    number gen_01_slide_920_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_920_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_920_prev = this->gen_01_slide_920_prev + ((x > this->gen_01_slide_920_prev ? iup : idown)) * temp;
        return this->gen_01_slide_920_prev;
    }
    
    void gen_01_slide_920_reset() {
        this->gen_01_slide_920_prev = 0;
    }
    
    void gen_01_noise_922_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_922_state
        );
    }
    
    void gen_01_noise_922_init() {
        this->gen_01_noise_922_reset();
    }
    
    void gen_01_noise_922_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_922_state);
    }
    
    number gen_01_noise_922_next() {
        return xoshiro_next(this->gen_01_noise_922_state);
    }
    
    number gen_01_slide_931_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_931_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_931_prev = this->gen_01_slide_931_prev + ((x > this->gen_01_slide_931_prev ? iup : idown)) * temp;
        return this->gen_01_slide_931_prev;
    }
    
    void gen_01_slide_931_reset() {
        this->gen_01_slide_931_prev = 0;
    }
    
    number gen_01_phasor_933_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_933_conv;
    
        if (this->gen_01_phasor_933_currentPhase < 0.)
            this->gen_01_phasor_933_currentPhase = 1. + this->gen_01_phasor_933_currentPhase;
    
        if (this->gen_01_phasor_933_currentPhase > 1.)
            this->gen_01_phasor_933_currentPhase = this->gen_01_phasor_933_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_933_currentPhase;
        this->gen_01_phasor_933_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_933_reset() {
        this->gen_01_phasor_933_currentPhase = 0;
    }
    
    void gen_01_phasor_933_dspsetup() {
        this->gen_01_phasor_933_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_935_next(number x) {
        number temp = (number)(x - this->gen_01_delta_935_prev);
        this->gen_01_delta_935_prev = x;
        return temp;
    }
    
    void gen_01_delta_935_dspsetup() {
        this->gen_01_delta_935_reset();
    }
    
    void gen_01_delta_935_reset() {
        this->gen_01_delta_935_prev = 0;
    }
    
    array<number, 3> gen_01_counter_938_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_938_count = 0;
            this->gen_01_counter_938_carry = 0;
        } else {
            this->gen_01_counter_938_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_938_count >= limit) || (a < 0 && this->gen_01_counter_938_count <= limit)) {
                    this->gen_01_counter_938_count = 0;
                    this->gen_01_counter_938_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {this->gen_01_counter_938_count, carry_flag, this->gen_01_counter_938_carry};
    }
    
    void gen_01_counter_938_init() {
        this->gen_01_counter_938_count = 0;
    }
    
    void gen_01_counter_938_reset() {
        this->gen_01_counter_938_carry = 0;
        this->gen_01_counter_938_count = 0;
    }
    
    number gen_01_delta_941_next(number x) {
        number temp = (number)(x - this->gen_01_delta_941_prev);
        this->gen_01_delta_941_prev = x;
        return temp;
    }
    
    void gen_01_delta_941_dspsetup() {
        this->gen_01_delta_941_reset();
    }
    
    void gen_01_delta_941_reset() {
        this->gen_01_delta_941_prev = 0;
    }
    
    number gen_01_latch_945_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_945_value = x;
        }
    
        return this->gen_01_latch_945_value;
    }
    
    void gen_01_latch_945_dspsetup() {
        this->gen_01_latch_945_reset();
    }
    
    void gen_01_latch_945_init() {
        this->gen_01_latch_945_reset();
    }
    
    void gen_01_latch_945_reset() {
        this->gen_01_latch_945_value = 0;
    }
    
    number gen_01_latch_947_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_947_value = x;
        }
    
        return this->gen_01_latch_947_value;
    }
    
    void gen_01_latch_947_dspsetup() {
        this->gen_01_latch_947_reset();
    }
    
    void gen_01_latch_947_init() {
        this->gen_01_latch_947_reset();
    }
    
    void gen_01_latch_947_reset() {
        this->gen_01_latch_947_value = 0;
    }
    
    array<number, 3> gen_01_counter_955_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_955_count = 0;
            this->gen_01_counter_955_carry = 0;
        } else {
            this->gen_01_counter_955_count += a;
        }
    
        return {this->gen_01_counter_955_count, carry_flag, this->gen_01_counter_955_carry};
    }
    
    void gen_01_counter_955_init() {
        this->gen_01_counter_955_count = 0;
    }
    
    void gen_01_counter_955_reset() {
        this->gen_01_counter_955_carry = 0;
        this->gen_01_counter_955_count = 0;
    }
    
    void gen_01_noise_964_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_964_state
        );
    }
    
    void gen_01_noise_964_init() {
        this->gen_01_noise_964_reset();
    }
    
    void gen_01_noise_964_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_964_state);
    }
    
    number gen_01_noise_964_next() {
        return xoshiro_next(this->gen_01_noise_964_state);
    }
    
    void gen_01_noise_966_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_966_state
        );
    }
    
    void gen_01_noise_966_init() {
        this->gen_01_noise_966_reset();
    }
    
    void gen_01_noise_966_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_966_state);
    }
    
    number gen_01_noise_966_next() {
        return xoshiro_next(this->gen_01_noise_966_state);
    }
    
    number gen_01_slide_970_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_970_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_970_prev = this->gen_01_slide_970_prev + ((x > this->gen_01_slide_970_prev ? iup : idown)) * temp;
        return this->gen_01_slide_970_prev;
    }
    
    void gen_01_slide_970_reset() {
        this->gen_01_slide_970_prev = 0;
    }
    
    number gen_01_slide_980_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_980_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_980_prev = this->gen_01_slide_980_prev + ((x > this->gen_01_slide_980_prev ? iup : idown)) * temp;
        return this->gen_01_slide_980_prev;
    }
    
    void gen_01_slide_980_reset() {
        this->gen_01_slide_980_prev = 0;
    }
    
    number gen_01_latch_983_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_983_value = x;
        }
    
        return this->gen_01_latch_983_value;
    }
    
    void gen_01_latch_983_dspsetup() {
        this->gen_01_latch_983_reset();
    }
    
    void gen_01_latch_983_init() {
        this->gen_01_latch_983_reset();
    }
    
    void gen_01_latch_983_reset() {
        this->gen_01_latch_983_value = 0;
    }
    
    number gen_01_slide_986_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_986_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_986_prev = this->gen_01_slide_986_prev + ((x > this->gen_01_slide_986_prev ? iup : idown)) * temp;
        return this->gen_01_slide_986_prev;
    }
    
    void gen_01_slide_986_reset() {
        this->gen_01_slide_986_prev = 0;
    }
    
    number gen_01_slide_991_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_991_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_991_prev = this->gen_01_slide_991_prev + ((x > this->gen_01_slide_991_prev ? iup : idown)) * temp;
        return this->gen_01_slide_991_prev;
    }
    
    void gen_01_slide_991_reset() {
        this->gen_01_slide_991_prev = 0;
    }
    
    number gen_01_latch_997_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_997_value = x;
        }
    
        return this->gen_01_latch_997_value;
    }
    
    void gen_01_latch_997_dspsetup() {
        this->gen_01_latch_997_reset();
    }
    
    void gen_01_latch_997_init() {
        this->gen_01_latch_997_reset();
    }
    
    void gen_01_latch_997_reset() {
        this->gen_01_latch_997_value = 0;
    }
    
    number gen_01_slide_1015_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1015_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1015_prev = this->gen_01_slide_1015_prev + ((x > this->gen_01_slide_1015_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1015_prev;
    }
    
    void gen_01_slide_1015_reset() {
        this->gen_01_slide_1015_prev = 0;
    }
    
    void gen_01_noise_1017_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1017_state
        );
    }
    
    void gen_01_noise_1017_init() {
        this->gen_01_noise_1017_reset();
    }
    
    void gen_01_noise_1017_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1017_state);
    }
    
    number gen_01_noise_1017_next() {
        return xoshiro_next(this->gen_01_noise_1017_state);
    }
    
    number gen_01_slide_1023_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1023_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1023_prev = this->gen_01_slide_1023_prev + ((x > this->gen_01_slide_1023_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1023_prev;
    }
    
    void gen_01_slide_1023_reset() {
        this->gen_01_slide_1023_prev = 0;
    }
    
    number gen_01_phasor_1025_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1025_conv;
    
        if (this->gen_01_phasor_1025_currentPhase < 0.)
            this->gen_01_phasor_1025_currentPhase = 1. + this->gen_01_phasor_1025_currentPhase;
    
        if (this->gen_01_phasor_1025_currentPhase > 1.)
            this->gen_01_phasor_1025_currentPhase = this->gen_01_phasor_1025_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1025_currentPhase;
        this->gen_01_phasor_1025_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1025_reset() {
        this->gen_01_phasor_1025_currentPhase = 0;
    }
    
    void gen_01_phasor_1025_dspsetup() {
        this->gen_01_phasor_1025_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1027_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1027_prev);
        this->gen_01_delta_1027_prev = x;
        return temp;
    }
    
    void gen_01_delta_1027_dspsetup() {
        this->gen_01_delta_1027_reset();
    }
    
    void gen_01_delta_1027_reset() {
        this->gen_01_delta_1027_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1030_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1030_count = 0;
            this->gen_01_counter_1030_carry = 0;
        } else {
            this->gen_01_counter_1030_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1030_count >= limit) || (a < 0 && this->gen_01_counter_1030_count <= limit)) {
                    this->gen_01_counter_1030_count = 0;
                    this->gen_01_counter_1030_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1030_count,
            carry_flag,
            this->gen_01_counter_1030_carry
        };
    }
    
    void gen_01_counter_1030_init() {
        this->gen_01_counter_1030_count = 0;
    }
    
    void gen_01_counter_1030_reset() {
        this->gen_01_counter_1030_carry = 0;
        this->gen_01_counter_1030_count = 0;
    }
    
    number gen_01_delta_1033_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1033_prev);
        this->gen_01_delta_1033_prev = x;
        return temp;
    }
    
    void gen_01_delta_1033_dspsetup() {
        this->gen_01_delta_1033_reset();
    }
    
    void gen_01_delta_1033_reset() {
        this->gen_01_delta_1033_prev = 0;
    }
    
    number gen_01_latch_1037_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1037_value = x;
        }
    
        return this->gen_01_latch_1037_value;
    }
    
    void gen_01_latch_1037_dspsetup() {
        this->gen_01_latch_1037_reset();
    }
    
    void gen_01_latch_1037_init() {
        this->gen_01_latch_1037_reset();
    }
    
    void gen_01_latch_1037_reset() {
        this->gen_01_latch_1037_value = 0;
    }
    
    number gen_01_latch_1039_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1039_value = x;
        }
    
        return this->gen_01_latch_1039_value;
    }
    
    void gen_01_latch_1039_dspsetup() {
        this->gen_01_latch_1039_reset();
    }
    
    void gen_01_latch_1039_init() {
        this->gen_01_latch_1039_reset();
    }
    
    void gen_01_latch_1039_reset() {
        this->gen_01_latch_1039_value = 0;
    }
    
    array<number, 3> gen_01_counter_1047_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1047_count = 0;
            this->gen_01_counter_1047_carry = 0;
        } else {
            this->gen_01_counter_1047_count += a;
        }
    
        return {
            this->gen_01_counter_1047_count,
            carry_flag,
            this->gen_01_counter_1047_carry
        };
    }
    
    void gen_01_counter_1047_init() {
        this->gen_01_counter_1047_count = 0;
    }
    
    void gen_01_counter_1047_reset() {
        this->gen_01_counter_1047_carry = 0;
        this->gen_01_counter_1047_count = 0;
    }
    
    void gen_01_noise_1059_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1059_state
        );
    }
    
    void gen_01_noise_1059_init() {
        this->gen_01_noise_1059_reset();
    }
    
    void gen_01_noise_1059_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1059_state);
    }
    
    number gen_01_noise_1059_next() {
        return xoshiro_next(this->gen_01_noise_1059_state);
    }
    
    void gen_01_noise_1061_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1061_state
        );
    }
    
    void gen_01_noise_1061_init() {
        this->gen_01_noise_1061_reset();
    }
    
    void gen_01_noise_1061_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1061_state);
    }
    
    number gen_01_noise_1061_next() {
        return xoshiro_next(this->gen_01_noise_1061_state);
    }
    
    number gen_01_slide_1065_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1065_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1065_prev = this->gen_01_slide_1065_prev + ((x > this->gen_01_slide_1065_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1065_prev;
    }
    
    void gen_01_slide_1065_reset() {
        this->gen_01_slide_1065_prev = 0;
    }
    
    number gen_01_slide_1075_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1075_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1075_prev = this->gen_01_slide_1075_prev + ((x > this->gen_01_slide_1075_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1075_prev;
    }
    
    void gen_01_slide_1075_reset() {
        this->gen_01_slide_1075_prev = 0;
    }
    
    number gen_01_latch_1078_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1078_value = x;
        }
    
        return this->gen_01_latch_1078_value;
    }
    
    void gen_01_latch_1078_dspsetup() {
        this->gen_01_latch_1078_reset();
    }
    
    void gen_01_latch_1078_init() {
        this->gen_01_latch_1078_reset();
    }
    
    void gen_01_latch_1078_reset() {
        this->gen_01_latch_1078_value = 0;
    }
    
    number gen_01_slide_1081_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1081_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1081_prev = this->gen_01_slide_1081_prev + ((x > this->gen_01_slide_1081_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1081_prev;
    }
    
    void gen_01_slide_1081_reset() {
        this->gen_01_slide_1081_prev = 0;
    }
    
    number gen_01_slide_1086_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1086_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1086_prev = this->gen_01_slide_1086_prev + ((x > this->gen_01_slide_1086_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1086_prev;
    }
    
    void gen_01_slide_1086_reset() {
        this->gen_01_slide_1086_prev = 0;
    }
    
    number gen_01_latch_1092_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1092_value = x;
        }
    
        return this->gen_01_latch_1092_value;
    }
    
    void gen_01_latch_1092_dspsetup() {
        this->gen_01_latch_1092_reset();
    }
    
    void gen_01_latch_1092_init() {
        this->gen_01_latch_1092_reset();
    }
    
    void gen_01_latch_1092_reset() {
        this->gen_01_latch_1092_value = 0;
    }
    
    number gen_01_slide_1110_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1110_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1110_prev = this->gen_01_slide_1110_prev + ((x > this->gen_01_slide_1110_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1110_prev;
    }
    
    void gen_01_slide_1110_reset() {
        this->gen_01_slide_1110_prev = 0;
    }
    
    void gen_01_noise_1112_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1112_state
        );
    }
    
    void gen_01_noise_1112_init() {
        this->gen_01_noise_1112_reset();
    }
    
    void gen_01_noise_1112_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1112_state);
    }
    
    number gen_01_noise_1112_next() {
        return xoshiro_next(this->gen_01_noise_1112_state);
    }
    
    number gen_01_slide_1121_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1121_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1121_prev = this->gen_01_slide_1121_prev + ((x > this->gen_01_slide_1121_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1121_prev;
    }
    
    void gen_01_slide_1121_reset() {
        this->gen_01_slide_1121_prev = 0;
    }
    
    number gen_01_phasor_1123_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1123_conv;
    
        if (this->gen_01_phasor_1123_currentPhase < 0.)
            this->gen_01_phasor_1123_currentPhase = 1. + this->gen_01_phasor_1123_currentPhase;
    
        if (this->gen_01_phasor_1123_currentPhase > 1.)
            this->gen_01_phasor_1123_currentPhase = this->gen_01_phasor_1123_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1123_currentPhase;
        this->gen_01_phasor_1123_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1123_reset() {
        this->gen_01_phasor_1123_currentPhase = 0;
    }
    
    void gen_01_phasor_1123_dspsetup() {
        this->gen_01_phasor_1123_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1125_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1125_prev);
        this->gen_01_delta_1125_prev = x;
        return temp;
    }
    
    void gen_01_delta_1125_dspsetup() {
        this->gen_01_delta_1125_reset();
    }
    
    void gen_01_delta_1125_reset() {
        this->gen_01_delta_1125_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1128_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1128_count = 0;
            this->gen_01_counter_1128_carry = 0;
        } else {
            this->gen_01_counter_1128_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1128_count >= limit) || (a < 0 && this->gen_01_counter_1128_count <= limit)) {
                    this->gen_01_counter_1128_count = 0;
                    this->gen_01_counter_1128_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1128_count,
            carry_flag,
            this->gen_01_counter_1128_carry
        };
    }
    
    void gen_01_counter_1128_init() {
        this->gen_01_counter_1128_count = 0;
    }
    
    void gen_01_counter_1128_reset() {
        this->gen_01_counter_1128_carry = 0;
        this->gen_01_counter_1128_count = 0;
    }
    
    number gen_01_delta_1131_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1131_prev);
        this->gen_01_delta_1131_prev = x;
        return temp;
    }
    
    void gen_01_delta_1131_dspsetup() {
        this->gen_01_delta_1131_reset();
    }
    
    void gen_01_delta_1131_reset() {
        this->gen_01_delta_1131_prev = 0;
    }
    
    number gen_01_latch_1136_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1136_value = x;
        }
    
        return this->gen_01_latch_1136_value;
    }
    
    void gen_01_latch_1136_dspsetup() {
        this->gen_01_latch_1136_reset();
    }
    
    void gen_01_latch_1136_init() {
        this->gen_01_latch_1136_reset();
    }
    
    void gen_01_latch_1136_reset() {
        this->gen_01_latch_1136_value = 0;
    }
    
    number gen_01_latch_1144_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1144_value = x;
        }
    
        return this->gen_01_latch_1144_value;
    }
    
    void gen_01_latch_1144_dspsetup() {
        this->gen_01_latch_1144_reset();
    }
    
    void gen_01_latch_1144_init() {
        this->gen_01_latch_1144_reset();
    }
    
    void gen_01_latch_1144_reset() {
        this->gen_01_latch_1144_value = 0;
    }
    
    array<number, 3> gen_01_counter_1146_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1146_count = 0;
            this->gen_01_counter_1146_carry = 0;
        } else {
            this->gen_01_counter_1146_count += a;
        }
    
        return {
            this->gen_01_counter_1146_count,
            carry_flag,
            this->gen_01_counter_1146_carry
        };
    }
    
    void gen_01_counter_1146_init() {
        this->gen_01_counter_1146_count = 0;
    }
    
    void gen_01_counter_1146_reset() {
        this->gen_01_counter_1146_carry = 0;
        this->gen_01_counter_1146_count = 0;
    }
    
    void gen_01_noise_1155_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1155_state
        );
    }
    
    void gen_01_noise_1155_init() {
        this->gen_01_noise_1155_reset();
    }
    
    void gen_01_noise_1155_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1155_state);
    }
    
    number gen_01_noise_1155_next() {
        return xoshiro_next(this->gen_01_noise_1155_state);
    }
    
    void gen_01_noise_1157_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1157_state
        );
    }
    
    void gen_01_noise_1157_init() {
        this->gen_01_noise_1157_reset();
    }
    
    void gen_01_noise_1157_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1157_state);
    }
    
    number gen_01_noise_1157_next() {
        return xoshiro_next(this->gen_01_noise_1157_state);
    }
    
    number gen_01_slide_1161_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1161_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1161_prev = this->gen_01_slide_1161_prev + ((x > this->gen_01_slide_1161_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1161_prev;
    }
    
    void gen_01_slide_1161_reset() {
        this->gen_01_slide_1161_prev = 0;
    }
    
    number gen_01_slide_1171_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1171_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1171_prev = this->gen_01_slide_1171_prev + ((x > this->gen_01_slide_1171_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1171_prev;
    }
    
    void gen_01_slide_1171_reset() {
        this->gen_01_slide_1171_prev = 0;
    }
    
    number gen_01_latch_1174_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1174_value = x;
        }
    
        return this->gen_01_latch_1174_value;
    }
    
    void gen_01_latch_1174_dspsetup() {
        this->gen_01_latch_1174_reset();
    }
    
    void gen_01_latch_1174_init() {
        this->gen_01_latch_1174_reset();
    }
    
    void gen_01_latch_1174_reset() {
        this->gen_01_latch_1174_value = 0;
    }
    
    number gen_01_slide_1177_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1177_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1177_prev = this->gen_01_slide_1177_prev + ((x > this->gen_01_slide_1177_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1177_prev;
    }
    
    void gen_01_slide_1177_reset() {
        this->gen_01_slide_1177_prev = 0;
    }
    
    number gen_01_slide_1182_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1182_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1182_prev = this->gen_01_slide_1182_prev + ((x > this->gen_01_slide_1182_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1182_prev;
    }
    
    void gen_01_slide_1182_reset() {
        this->gen_01_slide_1182_prev = 0;
    }
    
    number gen_01_latch_1188_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1188_value = x;
        }
    
        return this->gen_01_latch_1188_value;
    }
    
    void gen_01_latch_1188_dspsetup() {
        this->gen_01_latch_1188_reset();
    }
    
    void gen_01_latch_1188_init() {
        this->gen_01_latch_1188_reset();
    }
    
    void gen_01_latch_1188_reset() {
        this->gen_01_latch_1188_value = 0;
    }
    
    number gen_01_slide_1206_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1206_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1206_prev = this->gen_01_slide_1206_prev + ((x > this->gen_01_slide_1206_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1206_prev;
    }
    
    void gen_01_slide_1206_reset() {
        this->gen_01_slide_1206_prev = 0;
    }
    
    void gen_01_noise_1208_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1208_state
        );
    }
    
    void gen_01_noise_1208_init() {
        this->gen_01_noise_1208_reset();
    }
    
    void gen_01_noise_1208_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1208_state);
    }
    
    number gen_01_noise_1208_next() {
        return xoshiro_next(this->gen_01_noise_1208_state);
    }
    
    number gen_01_slide_1217_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1217_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1217_prev = this->gen_01_slide_1217_prev + ((x > this->gen_01_slide_1217_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1217_prev;
    }
    
    void gen_01_slide_1217_reset() {
        this->gen_01_slide_1217_prev = 0;
    }
    
    number gen_01_phasor_1219_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1219_conv;
    
        if (this->gen_01_phasor_1219_currentPhase < 0.)
            this->gen_01_phasor_1219_currentPhase = 1. + this->gen_01_phasor_1219_currentPhase;
    
        if (this->gen_01_phasor_1219_currentPhase > 1.)
            this->gen_01_phasor_1219_currentPhase = this->gen_01_phasor_1219_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1219_currentPhase;
        this->gen_01_phasor_1219_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1219_reset() {
        this->gen_01_phasor_1219_currentPhase = 0;
    }
    
    void gen_01_phasor_1219_dspsetup() {
        this->gen_01_phasor_1219_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1221_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1221_prev);
        this->gen_01_delta_1221_prev = x;
        return temp;
    }
    
    void gen_01_delta_1221_dspsetup() {
        this->gen_01_delta_1221_reset();
    }
    
    void gen_01_delta_1221_reset() {
        this->gen_01_delta_1221_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1224_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1224_count = 0;
            this->gen_01_counter_1224_carry = 0;
        } else {
            this->gen_01_counter_1224_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1224_count >= limit) || (a < 0 && this->gen_01_counter_1224_count <= limit)) {
                    this->gen_01_counter_1224_count = 0;
                    this->gen_01_counter_1224_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1224_count,
            carry_flag,
            this->gen_01_counter_1224_carry
        };
    }
    
    void gen_01_counter_1224_init() {
        this->gen_01_counter_1224_count = 0;
    }
    
    void gen_01_counter_1224_reset() {
        this->gen_01_counter_1224_carry = 0;
        this->gen_01_counter_1224_count = 0;
    }
    
    number gen_01_delta_1227_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1227_prev);
        this->gen_01_delta_1227_prev = x;
        return temp;
    }
    
    void gen_01_delta_1227_dspsetup() {
        this->gen_01_delta_1227_reset();
    }
    
    void gen_01_delta_1227_reset() {
        this->gen_01_delta_1227_prev = 0;
    }
    
    number gen_01_latch_1231_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1231_value = x;
        }
    
        return this->gen_01_latch_1231_value;
    }
    
    void gen_01_latch_1231_dspsetup() {
        this->gen_01_latch_1231_reset();
    }
    
    void gen_01_latch_1231_init() {
        this->gen_01_latch_1231_reset();
    }
    
    void gen_01_latch_1231_reset() {
        this->gen_01_latch_1231_value = 0;
    }
    
    number gen_01_latch_1239_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1239_value = x;
        }
    
        return this->gen_01_latch_1239_value;
    }
    
    void gen_01_latch_1239_dspsetup() {
        this->gen_01_latch_1239_reset();
    }
    
    void gen_01_latch_1239_init() {
        this->gen_01_latch_1239_reset();
    }
    
    void gen_01_latch_1239_reset() {
        this->gen_01_latch_1239_value = 0;
    }
    
    array<number, 3> gen_01_counter_1241_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1241_count = 0;
            this->gen_01_counter_1241_carry = 0;
        } else {
            this->gen_01_counter_1241_count += a;
        }
    
        return {
            this->gen_01_counter_1241_count,
            carry_flag,
            this->gen_01_counter_1241_carry
        };
    }
    
    void gen_01_counter_1241_init() {
        this->gen_01_counter_1241_count = 0;
    }
    
    void gen_01_counter_1241_reset() {
        this->gen_01_counter_1241_carry = 0;
        this->gen_01_counter_1241_count = 0;
    }
    
    void gen_01_noise_1250_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1250_state
        );
    }
    
    void gen_01_noise_1250_init() {
        this->gen_01_noise_1250_reset();
    }
    
    void gen_01_noise_1250_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1250_state);
    }
    
    number gen_01_noise_1250_next() {
        return xoshiro_next(this->gen_01_noise_1250_state);
    }
    
    void gen_01_noise_1252_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1252_state
        );
    }
    
    void gen_01_noise_1252_init() {
        this->gen_01_noise_1252_reset();
    }
    
    void gen_01_noise_1252_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1252_state);
    }
    
    number gen_01_noise_1252_next() {
        return xoshiro_next(this->gen_01_noise_1252_state);
    }
    
    number gen_01_slide_1256_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1256_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1256_prev = this->gen_01_slide_1256_prev + ((x > this->gen_01_slide_1256_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1256_prev;
    }
    
    void gen_01_slide_1256_reset() {
        this->gen_01_slide_1256_prev = 0;
    }
    
    number gen_01_slide_1266_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1266_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1266_prev = this->gen_01_slide_1266_prev + ((x > this->gen_01_slide_1266_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1266_prev;
    }
    
    void gen_01_slide_1266_reset() {
        this->gen_01_slide_1266_prev = 0;
    }
    
    number gen_01_latch_1269_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1269_value = x;
        }
    
        return this->gen_01_latch_1269_value;
    }
    
    void gen_01_latch_1269_dspsetup() {
        this->gen_01_latch_1269_reset();
    }
    
    void gen_01_latch_1269_init() {
        this->gen_01_latch_1269_reset();
    }
    
    void gen_01_latch_1269_reset() {
        this->gen_01_latch_1269_value = 0;
    }
    
    number gen_01_slide_1272_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1272_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1272_prev = this->gen_01_slide_1272_prev + ((x > this->gen_01_slide_1272_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1272_prev;
    }
    
    void gen_01_slide_1272_reset() {
        this->gen_01_slide_1272_prev = 0;
    }
    
    number gen_01_slide_1278_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1278_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1278_prev = this->gen_01_slide_1278_prev + ((x > this->gen_01_slide_1278_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1278_prev;
    }
    
    void gen_01_slide_1278_reset() {
        this->gen_01_slide_1278_prev = 0;
    }
    
    number gen_01_latch_1284_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1284_value = x;
        }
    
        return this->gen_01_latch_1284_value;
    }
    
    void gen_01_latch_1284_dspsetup() {
        this->gen_01_latch_1284_reset();
    }
    
    void gen_01_latch_1284_init() {
        this->gen_01_latch_1284_reset();
    }
    
    void gen_01_latch_1284_reset() {
        this->gen_01_latch_1284_value = 0;
    }
    
    number gen_01_slide_1302_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1302_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1302_prev = this->gen_01_slide_1302_prev + ((x > this->gen_01_slide_1302_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1302_prev;
    }
    
    void gen_01_slide_1302_reset() {
        this->gen_01_slide_1302_prev = 0;
    }
    
    void gen_01_noise_1304_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1304_state
        );
    }
    
    void gen_01_noise_1304_init() {
        this->gen_01_noise_1304_reset();
    }
    
    void gen_01_noise_1304_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1304_state);
    }
    
    number gen_01_noise_1304_next() {
        return xoshiro_next(this->gen_01_noise_1304_state);
    }
    
    number gen_01_slide_1313_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1313_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1313_prev = this->gen_01_slide_1313_prev + ((x > this->gen_01_slide_1313_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1313_prev;
    }
    
    void gen_01_slide_1313_reset() {
        this->gen_01_slide_1313_prev = 0;
    }
    
    number gen_01_phasor_1315_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1315_conv;
    
        if (this->gen_01_phasor_1315_currentPhase < 0.)
            this->gen_01_phasor_1315_currentPhase = 1. + this->gen_01_phasor_1315_currentPhase;
    
        if (this->gen_01_phasor_1315_currentPhase > 1.)
            this->gen_01_phasor_1315_currentPhase = this->gen_01_phasor_1315_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1315_currentPhase;
        this->gen_01_phasor_1315_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1315_reset() {
        this->gen_01_phasor_1315_currentPhase = 0;
    }
    
    void gen_01_phasor_1315_dspsetup() {
        this->gen_01_phasor_1315_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1317_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1317_prev);
        this->gen_01_delta_1317_prev = x;
        return temp;
    }
    
    void gen_01_delta_1317_dspsetup() {
        this->gen_01_delta_1317_reset();
    }
    
    void gen_01_delta_1317_reset() {
        this->gen_01_delta_1317_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1320_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1320_count = 0;
            this->gen_01_counter_1320_carry = 0;
        } else {
            this->gen_01_counter_1320_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1320_count >= limit) || (a < 0 && this->gen_01_counter_1320_count <= limit)) {
                    this->gen_01_counter_1320_count = 0;
                    this->gen_01_counter_1320_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1320_count,
            carry_flag,
            this->gen_01_counter_1320_carry
        };
    }
    
    void gen_01_counter_1320_init() {
        this->gen_01_counter_1320_count = 0;
    }
    
    void gen_01_counter_1320_reset() {
        this->gen_01_counter_1320_carry = 0;
        this->gen_01_counter_1320_count = 0;
    }
    
    number gen_01_delta_1323_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1323_prev);
        this->gen_01_delta_1323_prev = x;
        return temp;
    }
    
    void gen_01_delta_1323_dspsetup() {
        this->gen_01_delta_1323_reset();
    }
    
    void gen_01_delta_1323_reset() {
        this->gen_01_delta_1323_prev = 0;
    }
    
    number gen_01_latch_1327_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1327_value = x;
        }
    
        return this->gen_01_latch_1327_value;
    }
    
    void gen_01_latch_1327_dspsetup() {
        this->gen_01_latch_1327_reset();
    }
    
    void gen_01_latch_1327_init() {
        this->gen_01_latch_1327_reset();
    }
    
    void gen_01_latch_1327_reset() {
        this->gen_01_latch_1327_value = 0;
    }
    
    number gen_01_latch_1335_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1335_value = x;
        }
    
        return this->gen_01_latch_1335_value;
    }
    
    void gen_01_latch_1335_dspsetup() {
        this->gen_01_latch_1335_reset();
    }
    
    void gen_01_latch_1335_init() {
        this->gen_01_latch_1335_reset();
    }
    
    void gen_01_latch_1335_reset() {
        this->gen_01_latch_1335_value = 0;
    }
    
    array<number, 3> gen_01_counter_1337_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1337_count = 0;
            this->gen_01_counter_1337_carry = 0;
        } else {
            this->gen_01_counter_1337_count += a;
        }
    
        return {
            this->gen_01_counter_1337_count,
            carry_flag,
            this->gen_01_counter_1337_carry
        };
    }
    
    void gen_01_counter_1337_init() {
        this->gen_01_counter_1337_count = 0;
    }
    
    void gen_01_counter_1337_reset() {
        this->gen_01_counter_1337_carry = 0;
        this->gen_01_counter_1337_count = 0;
    }
    
    void gen_01_noise_1346_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1346_state
        );
    }
    
    void gen_01_noise_1346_init() {
        this->gen_01_noise_1346_reset();
    }
    
    void gen_01_noise_1346_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1346_state);
    }
    
    number gen_01_noise_1346_next() {
        return xoshiro_next(this->gen_01_noise_1346_state);
    }
    
    void gen_01_noise_1348_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1348_state
        );
    }
    
    void gen_01_noise_1348_init() {
        this->gen_01_noise_1348_reset();
    }
    
    void gen_01_noise_1348_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1348_state);
    }
    
    number gen_01_noise_1348_next() {
        return xoshiro_next(this->gen_01_noise_1348_state);
    }
    
    number gen_01_slide_1352_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1352_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1352_prev = this->gen_01_slide_1352_prev + ((x > this->gen_01_slide_1352_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1352_prev;
    }
    
    void gen_01_slide_1352_reset() {
        this->gen_01_slide_1352_prev = 0;
    }
    
    number gen_01_slide_1362_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1362_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1362_prev = this->gen_01_slide_1362_prev + ((x > this->gen_01_slide_1362_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1362_prev;
    }
    
    void gen_01_slide_1362_reset() {
        this->gen_01_slide_1362_prev = 0;
    }
    
    number gen_01_latch_1365_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1365_value = x;
        }
    
        return this->gen_01_latch_1365_value;
    }
    
    void gen_01_latch_1365_dspsetup() {
        this->gen_01_latch_1365_reset();
    }
    
    void gen_01_latch_1365_init() {
        this->gen_01_latch_1365_reset();
    }
    
    void gen_01_latch_1365_reset() {
        this->gen_01_latch_1365_value = 0;
    }
    
    number gen_01_slide_1369_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1369_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1369_prev = this->gen_01_slide_1369_prev + ((x > this->gen_01_slide_1369_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1369_prev;
    }
    
    void gen_01_slide_1369_reset() {
        this->gen_01_slide_1369_prev = 0;
    }
    
    number gen_01_slide_1374_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1374_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1374_prev = this->gen_01_slide_1374_prev + ((x > this->gen_01_slide_1374_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1374_prev;
    }
    
    void gen_01_slide_1374_reset() {
        this->gen_01_slide_1374_prev = 0;
    }
    
    number gen_01_latch_1380_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1380_value = x;
        }
    
        return this->gen_01_latch_1380_value;
    }
    
    void gen_01_latch_1380_dspsetup() {
        this->gen_01_latch_1380_reset();
    }
    
    void gen_01_latch_1380_init() {
        this->gen_01_latch_1380_reset();
    }
    
    void gen_01_latch_1380_reset() {
        this->gen_01_latch_1380_value = 0;
    }
    
    number gen_01_slide_1398_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1398_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1398_prev = this->gen_01_slide_1398_prev + ((x > this->gen_01_slide_1398_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1398_prev;
    }
    
    void gen_01_slide_1398_reset() {
        this->gen_01_slide_1398_prev = 0;
    }
    
    void gen_01_noise_1401_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1401_state
        );
    }
    
    void gen_01_noise_1401_init() {
        this->gen_01_noise_1401_reset();
    }
    
    void gen_01_noise_1401_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1401_state);
    }
    
    number gen_01_noise_1401_next() {
        return xoshiro_next(this->gen_01_noise_1401_state);
    }
    
    number gen_01_slide_1410_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1410_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1410_prev = this->gen_01_slide_1410_prev + ((x > this->gen_01_slide_1410_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1410_prev;
    }
    
    void gen_01_slide_1410_reset() {
        this->gen_01_slide_1410_prev = 0;
    }
    
    number gen_01_phasor_1412_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1412_conv;
    
        if (this->gen_01_phasor_1412_currentPhase < 0.)
            this->gen_01_phasor_1412_currentPhase = 1. + this->gen_01_phasor_1412_currentPhase;
    
        if (this->gen_01_phasor_1412_currentPhase > 1.)
            this->gen_01_phasor_1412_currentPhase = this->gen_01_phasor_1412_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1412_currentPhase;
        this->gen_01_phasor_1412_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1412_reset() {
        this->gen_01_phasor_1412_currentPhase = 0;
    }
    
    void gen_01_phasor_1412_dspsetup() {
        this->gen_01_phasor_1412_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1414_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1414_prev);
        this->gen_01_delta_1414_prev = x;
        return temp;
    }
    
    void gen_01_delta_1414_dspsetup() {
        this->gen_01_delta_1414_reset();
    }
    
    void gen_01_delta_1414_reset() {
        this->gen_01_delta_1414_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1417_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1417_count = 0;
            this->gen_01_counter_1417_carry = 0;
        } else {
            this->gen_01_counter_1417_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1417_count >= limit) || (a < 0 && this->gen_01_counter_1417_count <= limit)) {
                    this->gen_01_counter_1417_count = 0;
                    this->gen_01_counter_1417_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1417_count,
            carry_flag,
            this->gen_01_counter_1417_carry
        };
    }
    
    void gen_01_counter_1417_init() {
        this->gen_01_counter_1417_count = 0;
    }
    
    void gen_01_counter_1417_reset() {
        this->gen_01_counter_1417_carry = 0;
        this->gen_01_counter_1417_count = 0;
    }
    
    number gen_01_delta_1420_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1420_prev);
        this->gen_01_delta_1420_prev = x;
        return temp;
    }
    
    void gen_01_delta_1420_dspsetup() {
        this->gen_01_delta_1420_reset();
    }
    
    void gen_01_delta_1420_reset() {
        this->gen_01_delta_1420_prev = 0;
    }
    
    number gen_01_latch_1424_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1424_value = x;
        }
    
        return this->gen_01_latch_1424_value;
    }
    
    void gen_01_latch_1424_dspsetup() {
        this->gen_01_latch_1424_reset();
    }
    
    void gen_01_latch_1424_init() {
        this->gen_01_latch_1424_reset();
    }
    
    void gen_01_latch_1424_reset() {
        this->gen_01_latch_1424_value = 0;
    }
    
    number gen_01_latch_1432_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1432_value = x;
        }
    
        return this->gen_01_latch_1432_value;
    }
    
    void gen_01_latch_1432_dspsetup() {
        this->gen_01_latch_1432_reset();
    }
    
    void gen_01_latch_1432_init() {
        this->gen_01_latch_1432_reset();
    }
    
    void gen_01_latch_1432_reset() {
        this->gen_01_latch_1432_value = 0;
    }
    
    array<number, 3> gen_01_counter_1434_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1434_count = 0;
            this->gen_01_counter_1434_carry = 0;
        } else {
            this->gen_01_counter_1434_count += a;
        }
    
        return {
            this->gen_01_counter_1434_count,
            carry_flag,
            this->gen_01_counter_1434_carry
        };
    }
    
    void gen_01_counter_1434_init() {
        this->gen_01_counter_1434_count = 0;
    }
    
    void gen_01_counter_1434_reset() {
        this->gen_01_counter_1434_carry = 0;
        this->gen_01_counter_1434_count = 0;
    }
    
    void gen_01_noise_1443_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1443_state
        );
    }
    
    void gen_01_noise_1443_init() {
        this->gen_01_noise_1443_reset();
    }
    
    void gen_01_noise_1443_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1443_state);
    }
    
    number gen_01_noise_1443_next() {
        return xoshiro_next(this->gen_01_noise_1443_state);
    }
    
    void gen_01_noise_1445_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1445_state
        );
    }
    
    void gen_01_noise_1445_init() {
        this->gen_01_noise_1445_reset();
    }
    
    void gen_01_noise_1445_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1445_state);
    }
    
    number gen_01_noise_1445_next() {
        return xoshiro_next(this->gen_01_noise_1445_state);
    }
    
    number gen_01_slide_1449_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1449_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1449_prev = this->gen_01_slide_1449_prev + ((x > this->gen_01_slide_1449_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1449_prev;
    }
    
    void gen_01_slide_1449_reset() {
        this->gen_01_slide_1449_prev = 0;
    }
    
    number gen_01_slide_1459_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1459_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1459_prev = this->gen_01_slide_1459_prev + ((x > this->gen_01_slide_1459_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1459_prev;
    }
    
    void gen_01_slide_1459_reset() {
        this->gen_01_slide_1459_prev = 0;
    }
    
    number gen_01_latch_1462_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1462_value = x;
        }
    
        return this->gen_01_latch_1462_value;
    }
    
    void gen_01_latch_1462_dspsetup() {
        this->gen_01_latch_1462_reset();
    }
    
    void gen_01_latch_1462_init() {
        this->gen_01_latch_1462_reset();
    }
    
    void gen_01_latch_1462_reset() {
        this->gen_01_latch_1462_value = 0;
    }
    
    number gen_01_slide_1465_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1465_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1465_prev = this->gen_01_slide_1465_prev + ((x > this->gen_01_slide_1465_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1465_prev;
    }
    
    void gen_01_slide_1465_reset() {
        this->gen_01_slide_1465_prev = 0;
    }
    
    number gen_01_slide_1470_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1470_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1470_prev = this->gen_01_slide_1470_prev + ((x > this->gen_01_slide_1470_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1470_prev;
    }
    
    void gen_01_slide_1470_reset() {
        this->gen_01_slide_1470_prev = 0;
    }
    
    number gen_01_latch_1476_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1476_value = x;
        }
    
        return this->gen_01_latch_1476_value;
    }
    
    void gen_01_latch_1476_dspsetup() {
        this->gen_01_latch_1476_reset();
    }
    
    void gen_01_latch_1476_init() {
        this->gen_01_latch_1476_reset();
    }
    
    void gen_01_latch_1476_reset() {
        this->gen_01_latch_1476_value = 0;
    }
    
    number gen_01_slide_1494_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1494_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1494_prev = this->gen_01_slide_1494_prev + ((x > this->gen_01_slide_1494_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1494_prev;
    }
    
    void gen_01_slide_1494_reset() {
        this->gen_01_slide_1494_prev = 0;
    }
    
    void gen_01_noise_1496_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1496_state
        );
    }
    
    void gen_01_noise_1496_init() {
        this->gen_01_noise_1496_reset();
    }
    
    void gen_01_noise_1496_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1496_state);
    }
    
    number gen_01_noise_1496_next() {
        return xoshiro_next(this->gen_01_noise_1496_state);
    }
    
    number gen_01_slide_1505_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1505_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1505_prev = this->gen_01_slide_1505_prev + ((x > this->gen_01_slide_1505_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1505_prev;
    }
    
    void gen_01_slide_1505_reset() {
        this->gen_01_slide_1505_prev = 0;
    }
    
    number gen_01_phasor_1507_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1507_conv;
    
        if (this->gen_01_phasor_1507_currentPhase < 0.)
            this->gen_01_phasor_1507_currentPhase = 1. + this->gen_01_phasor_1507_currentPhase;
    
        if (this->gen_01_phasor_1507_currentPhase > 1.)
            this->gen_01_phasor_1507_currentPhase = this->gen_01_phasor_1507_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1507_currentPhase;
        this->gen_01_phasor_1507_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1507_reset() {
        this->gen_01_phasor_1507_currentPhase = 0;
    }
    
    void gen_01_phasor_1507_dspsetup() {
        this->gen_01_phasor_1507_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1509_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1509_prev);
        this->gen_01_delta_1509_prev = x;
        return temp;
    }
    
    void gen_01_delta_1509_dspsetup() {
        this->gen_01_delta_1509_reset();
    }
    
    void gen_01_delta_1509_reset() {
        this->gen_01_delta_1509_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1512_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1512_count = 0;
            this->gen_01_counter_1512_carry = 0;
        } else {
            this->gen_01_counter_1512_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1512_count >= limit) || (a < 0 && this->gen_01_counter_1512_count <= limit)) {
                    this->gen_01_counter_1512_count = 0;
                    this->gen_01_counter_1512_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1512_count,
            carry_flag,
            this->gen_01_counter_1512_carry
        };
    }
    
    void gen_01_counter_1512_init() {
        this->gen_01_counter_1512_count = 0;
    }
    
    void gen_01_counter_1512_reset() {
        this->gen_01_counter_1512_carry = 0;
        this->gen_01_counter_1512_count = 0;
    }
    
    number gen_01_delta_1515_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1515_prev);
        this->gen_01_delta_1515_prev = x;
        return temp;
    }
    
    void gen_01_delta_1515_dspsetup() {
        this->gen_01_delta_1515_reset();
    }
    
    void gen_01_delta_1515_reset() {
        this->gen_01_delta_1515_prev = 0;
    }
    
    number gen_01_latch_1519_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1519_value = x;
        }
    
        return this->gen_01_latch_1519_value;
    }
    
    void gen_01_latch_1519_dspsetup() {
        this->gen_01_latch_1519_reset();
    }
    
    void gen_01_latch_1519_init() {
        this->gen_01_latch_1519_reset();
    }
    
    void gen_01_latch_1519_reset() {
        this->gen_01_latch_1519_value = 0;
    }
    
    number gen_01_latch_1527_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1527_value = x;
        }
    
        return this->gen_01_latch_1527_value;
    }
    
    void gen_01_latch_1527_dspsetup() {
        this->gen_01_latch_1527_reset();
    }
    
    void gen_01_latch_1527_init() {
        this->gen_01_latch_1527_reset();
    }
    
    void gen_01_latch_1527_reset() {
        this->gen_01_latch_1527_value = 0;
    }
    
    array<number, 3> gen_01_counter_1529_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1529_count = 0;
            this->gen_01_counter_1529_carry = 0;
        } else {
            this->gen_01_counter_1529_count += a;
        }
    
        return {
            this->gen_01_counter_1529_count,
            carry_flag,
            this->gen_01_counter_1529_carry
        };
    }
    
    void gen_01_counter_1529_init() {
        this->gen_01_counter_1529_count = 0;
    }
    
    void gen_01_counter_1529_reset() {
        this->gen_01_counter_1529_carry = 0;
        this->gen_01_counter_1529_count = 0;
    }
    
    void gen_01_noise_1538_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1538_state
        );
    }
    
    void gen_01_noise_1538_init() {
        this->gen_01_noise_1538_reset();
    }
    
    void gen_01_noise_1538_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1538_state);
    }
    
    number gen_01_noise_1538_next() {
        return xoshiro_next(this->gen_01_noise_1538_state);
    }
    
    void gen_01_noise_1540_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1540_state
        );
    }
    
    void gen_01_noise_1540_init() {
        this->gen_01_noise_1540_reset();
    }
    
    void gen_01_noise_1540_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1540_state);
    }
    
    number gen_01_noise_1540_next() {
        return xoshiro_next(this->gen_01_noise_1540_state);
    }
    
    number gen_01_slide_1544_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1544_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1544_prev = this->gen_01_slide_1544_prev + ((x > this->gen_01_slide_1544_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1544_prev;
    }
    
    void gen_01_slide_1544_reset() {
        this->gen_01_slide_1544_prev = 0;
    }
    
    number gen_01_slide_1554_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1554_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1554_prev = this->gen_01_slide_1554_prev + ((x > this->gen_01_slide_1554_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1554_prev;
    }
    
    void gen_01_slide_1554_reset() {
        this->gen_01_slide_1554_prev = 0;
    }
    
    number gen_01_latch_1557_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1557_value = x;
        }
    
        return this->gen_01_latch_1557_value;
    }
    
    void gen_01_latch_1557_dspsetup() {
        this->gen_01_latch_1557_reset();
    }
    
    void gen_01_latch_1557_init() {
        this->gen_01_latch_1557_reset();
    }
    
    void gen_01_latch_1557_reset() {
        this->gen_01_latch_1557_value = 0;
    }
    
    number gen_01_slide_1560_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1560_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1560_prev = this->gen_01_slide_1560_prev + ((x > this->gen_01_slide_1560_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1560_prev;
    }
    
    void gen_01_slide_1560_reset() {
        this->gen_01_slide_1560_prev = 0;
    }
    
    number gen_01_slide_1565_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1565_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1565_prev = this->gen_01_slide_1565_prev + ((x > this->gen_01_slide_1565_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1565_prev;
    }
    
    void gen_01_slide_1565_reset() {
        this->gen_01_slide_1565_prev = 0;
    }
    
    number gen_01_latch_1571_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1571_value = x;
        }
    
        return this->gen_01_latch_1571_value;
    }
    
    void gen_01_latch_1571_dspsetup() {
        this->gen_01_latch_1571_reset();
    }
    
    void gen_01_latch_1571_init() {
        this->gen_01_latch_1571_reset();
    }
    
    void gen_01_latch_1571_reset() {
        this->gen_01_latch_1571_value = 0;
    }
    
    number gen_01_slide_1589_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1589_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1589_prev = this->gen_01_slide_1589_prev + ((x > this->gen_01_slide_1589_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1589_prev;
    }
    
    void gen_01_slide_1589_reset() {
        this->gen_01_slide_1589_prev = 0;
    }
    
    void gen_01_noise_1591_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1591_state
        );
    }
    
    void gen_01_noise_1591_init() {
        this->gen_01_noise_1591_reset();
    }
    
    void gen_01_noise_1591_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1591_state);
    }
    
    number gen_01_noise_1591_next() {
        return xoshiro_next(this->gen_01_noise_1591_state);
    }
    
    number gen_01_slide_1597_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1597_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1597_prev = this->gen_01_slide_1597_prev + ((x > this->gen_01_slide_1597_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1597_prev;
    }
    
    void gen_01_slide_1597_reset() {
        this->gen_01_slide_1597_prev = 0;
    }
    
    number gen_01_phasor_1599_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1599_conv;
    
        if (this->gen_01_phasor_1599_currentPhase < 0.)
            this->gen_01_phasor_1599_currentPhase = 1. + this->gen_01_phasor_1599_currentPhase;
    
        if (this->gen_01_phasor_1599_currentPhase > 1.)
            this->gen_01_phasor_1599_currentPhase = this->gen_01_phasor_1599_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1599_currentPhase;
        this->gen_01_phasor_1599_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1599_reset() {
        this->gen_01_phasor_1599_currentPhase = 0;
    }
    
    void gen_01_phasor_1599_dspsetup() {
        this->gen_01_phasor_1599_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1601_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1601_prev);
        this->gen_01_delta_1601_prev = x;
        return temp;
    }
    
    void gen_01_delta_1601_dspsetup() {
        this->gen_01_delta_1601_reset();
    }
    
    void gen_01_delta_1601_reset() {
        this->gen_01_delta_1601_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1604_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1604_count = 0;
            this->gen_01_counter_1604_carry = 0;
        } else {
            this->gen_01_counter_1604_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1604_count >= limit) || (a < 0 && this->gen_01_counter_1604_count <= limit)) {
                    this->gen_01_counter_1604_count = 0;
                    this->gen_01_counter_1604_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1604_count,
            carry_flag,
            this->gen_01_counter_1604_carry
        };
    }
    
    void gen_01_counter_1604_init() {
        this->gen_01_counter_1604_count = 0;
    }
    
    void gen_01_counter_1604_reset() {
        this->gen_01_counter_1604_carry = 0;
        this->gen_01_counter_1604_count = 0;
    }
    
    number gen_01_delta_1607_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1607_prev);
        this->gen_01_delta_1607_prev = x;
        return temp;
    }
    
    void gen_01_delta_1607_dspsetup() {
        this->gen_01_delta_1607_reset();
    }
    
    void gen_01_delta_1607_reset() {
        this->gen_01_delta_1607_prev = 0;
    }
    
    number gen_01_latch_1611_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1611_value = x;
        }
    
        return this->gen_01_latch_1611_value;
    }
    
    void gen_01_latch_1611_dspsetup() {
        this->gen_01_latch_1611_reset();
    }
    
    void gen_01_latch_1611_init() {
        this->gen_01_latch_1611_reset();
    }
    
    void gen_01_latch_1611_reset() {
        this->gen_01_latch_1611_value = 0;
    }
    
    number gen_01_latch_1619_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1619_value = x;
        }
    
        return this->gen_01_latch_1619_value;
    }
    
    void gen_01_latch_1619_dspsetup() {
        this->gen_01_latch_1619_reset();
    }
    
    void gen_01_latch_1619_init() {
        this->gen_01_latch_1619_reset();
    }
    
    void gen_01_latch_1619_reset() {
        this->gen_01_latch_1619_value = 0;
    }
    
    array<number, 3> gen_01_counter_1621_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1621_count = 0;
            this->gen_01_counter_1621_carry = 0;
        } else {
            this->gen_01_counter_1621_count += a;
        }
    
        return {
            this->gen_01_counter_1621_count,
            carry_flag,
            this->gen_01_counter_1621_carry
        };
    }
    
    void gen_01_counter_1621_init() {
        this->gen_01_counter_1621_count = 0;
    }
    
    void gen_01_counter_1621_reset() {
        this->gen_01_counter_1621_carry = 0;
        this->gen_01_counter_1621_count = 0;
    }
    
    void gen_01_noise_1633_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1633_state
        );
    }
    
    void gen_01_noise_1633_init() {
        this->gen_01_noise_1633_reset();
    }
    
    void gen_01_noise_1633_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1633_state);
    }
    
    number gen_01_noise_1633_next() {
        return xoshiro_next(this->gen_01_noise_1633_state);
    }
    
    void gen_01_noise_1635_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1635_state
        );
    }
    
    void gen_01_noise_1635_init() {
        this->gen_01_noise_1635_reset();
    }
    
    void gen_01_noise_1635_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1635_state);
    }
    
    number gen_01_noise_1635_next() {
        return xoshiro_next(this->gen_01_noise_1635_state);
    }
    
    number gen_01_slide_1639_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1639_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1639_prev = this->gen_01_slide_1639_prev + ((x > this->gen_01_slide_1639_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1639_prev;
    }
    
    void gen_01_slide_1639_reset() {
        this->gen_01_slide_1639_prev = 0;
    }
    
    number gen_01_slide_1649_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1649_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1649_prev = this->gen_01_slide_1649_prev + ((x > this->gen_01_slide_1649_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1649_prev;
    }
    
    void gen_01_slide_1649_reset() {
        this->gen_01_slide_1649_prev = 0;
    }
    
    number gen_01_latch_1652_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1652_value = x;
        }
    
        return this->gen_01_latch_1652_value;
    }
    
    void gen_01_latch_1652_dspsetup() {
        this->gen_01_latch_1652_reset();
    }
    
    void gen_01_latch_1652_init() {
        this->gen_01_latch_1652_reset();
    }
    
    void gen_01_latch_1652_reset() {
        this->gen_01_latch_1652_value = 0;
    }
    
    number gen_01_slide_1655_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1655_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1655_prev = this->gen_01_slide_1655_prev + ((x > this->gen_01_slide_1655_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1655_prev;
    }
    
    void gen_01_slide_1655_reset() {
        this->gen_01_slide_1655_prev = 0;
    }
    
    number gen_01_slide_1660_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1660_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1660_prev = this->gen_01_slide_1660_prev + ((x > this->gen_01_slide_1660_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1660_prev;
    }
    
    void gen_01_slide_1660_reset() {
        this->gen_01_slide_1660_prev = 0;
    }
    
    number gen_01_latch_1667_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1667_value = x;
        }
    
        return this->gen_01_latch_1667_value;
    }
    
    void gen_01_latch_1667_dspsetup() {
        this->gen_01_latch_1667_reset();
    }
    
    void gen_01_latch_1667_init() {
        this->gen_01_latch_1667_reset();
    }
    
    void gen_01_latch_1667_reset() {
        this->gen_01_latch_1667_value = 0;
    }
    
    number gen_01_slide_1685_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1685_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1685_prev = this->gen_01_slide_1685_prev + ((x > this->gen_01_slide_1685_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1685_prev;
    }
    
    void gen_01_slide_1685_reset() {
        this->gen_01_slide_1685_prev = 0;
    }
    
    void gen_01_noise_1687_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1687_state
        );
    }
    
    void gen_01_noise_1687_init() {
        this->gen_01_noise_1687_reset();
    }
    
    void gen_01_noise_1687_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1687_state);
    }
    
    number gen_01_noise_1687_next() {
        return xoshiro_next(this->gen_01_noise_1687_state);
    }
    
    number gen_01_slide_1693_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1693_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1693_prev = this->gen_01_slide_1693_prev + ((x > this->gen_01_slide_1693_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1693_prev;
    }
    
    void gen_01_slide_1693_reset() {
        this->gen_01_slide_1693_prev = 0;
    }
    
    number gen_01_phasor_1695_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1695_conv;
    
        if (this->gen_01_phasor_1695_currentPhase < 0.)
            this->gen_01_phasor_1695_currentPhase = 1. + this->gen_01_phasor_1695_currentPhase;
    
        if (this->gen_01_phasor_1695_currentPhase > 1.)
            this->gen_01_phasor_1695_currentPhase = this->gen_01_phasor_1695_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1695_currentPhase;
        this->gen_01_phasor_1695_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1695_reset() {
        this->gen_01_phasor_1695_currentPhase = 0;
    }
    
    void gen_01_phasor_1695_dspsetup() {
        this->gen_01_phasor_1695_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1697_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1697_prev);
        this->gen_01_delta_1697_prev = x;
        return temp;
    }
    
    void gen_01_delta_1697_dspsetup() {
        this->gen_01_delta_1697_reset();
    }
    
    void gen_01_delta_1697_reset() {
        this->gen_01_delta_1697_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1700_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1700_count = 0;
            this->gen_01_counter_1700_carry = 0;
        } else {
            this->gen_01_counter_1700_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1700_count >= limit) || (a < 0 && this->gen_01_counter_1700_count <= limit)) {
                    this->gen_01_counter_1700_count = 0;
                    this->gen_01_counter_1700_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1700_count,
            carry_flag,
            this->gen_01_counter_1700_carry
        };
    }
    
    void gen_01_counter_1700_init() {
        this->gen_01_counter_1700_count = 0;
    }
    
    void gen_01_counter_1700_reset() {
        this->gen_01_counter_1700_carry = 0;
        this->gen_01_counter_1700_count = 0;
    }
    
    number gen_01_delta_1703_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1703_prev);
        this->gen_01_delta_1703_prev = x;
        return temp;
    }
    
    void gen_01_delta_1703_dspsetup() {
        this->gen_01_delta_1703_reset();
    }
    
    void gen_01_delta_1703_reset() {
        this->gen_01_delta_1703_prev = 0;
    }
    
    number gen_01_latch_1707_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1707_value = x;
        }
    
        return this->gen_01_latch_1707_value;
    }
    
    void gen_01_latch_1707_dspsetup() {
        this->gen_01_latch_1707_reset();
    }
    
    void gen_01_latch_1707_init() {
        this->gen_01_latch_1707_reset();
    }
    
    void gen_01_latch_1707_reset() {
        this->gen_01_latch_1707_value = 0;
    }
    
    number gen_01_latch_1710_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1710_value = x;
        }
    
        return this->gen_01_latch_1710_value;
    }
    
    void gen_01_latch_1710_dspsetup() {
        this->gen_01_latch_1710_reset();
    }
    
    void gen_01_latch_1710_init() {
        this->gen_01_latch_1710_reset();
    }
    
    void gen_01_latch_1710_reset() {
        this->gen_01_latch_1710_value = 0;
    }
    
    array<number, 3> gen_01_counter_1718_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1718_count = 0;
            this->gen_01_counter_1718_carry = 0;
        } else {
            this->gen_01_counter_1718_count += a;
        }
    
        return {
            this->gen_01_counter_1718_count,
            carry_flag,
            this->gen_01_counter_1718_carry
        };
    }
    
    void gen_01_counter_1718_init() {
        this->gen_01_counter_1718_count = 0;
    }
    
    void gen_01_counter_1718_reset() {
        this->gen_01_counter_1718_carry = 0;
        this->gen_01_counter_1718_count = 0;
    }
    
    void gen_01_noise_1730_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1730_state
        );
    }
    
    void gen_01_noise_1730_init() {
        this->gen_01_noise_1730_reset();
    }
    
    void gen_01_noise_1730_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1730_state);
    }
    
    number gen_01_noise_1730_next() {
        return xoshiro_next(this->gen_01_noise_1730_state);
    }
    
    void gen_01_noise_1732_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1732_state
        );
    }
    
    void gen_01_noise_1732_init() {
        this->gen_01_noise_1732_reset();
    }
    
    void gen_01_noise_1732_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1732_state);
    }
    
    number gen_01_noise_1732_next() {
        return xoshiro_next(this->gen_01_noise_1732_state);
    }
    
    number gen_01_slide_1736_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1736_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1736_prev = this->gen_01_slide_1736_prev + ((x > this->gen_01_slide_1736_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1736_prev;
    }
    
    void gen_01_slide_1736_reset() {
        this->gen_01_slide_1736_prev = 0;
    }
    
    number gen_01_slide_1746_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1746_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1746_prev = this->gen_01_slide_1746_prev + ((x > this->gen_01_slide_1746_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1746_prev;
    }
    
    void gen_01_slide_1746_reset() {
        this->gen_01_slide_1746_prev = 0;
    }
    
    number gen_01_latch_1749_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1749_value = x;
        }
    
        return this->gen_01_latch_1749_value;
    }
    
    void gen_01_latch_1749_dspsetup() {
        this->gen_01_latch_1749_reset();
    }
    
    void gen_01_latch_1749_init() {
        this->gen_01_latch_1749_reset();
    }
    
    void gen_01_latch_1749_reset() {
        this->gen_01_latch_1749_value = 0;
    }
    
    number gen_01_slide_1752_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1752_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1752_prev = this->gen_01_slide_1752_prev + ((x > this->gen_01_slide_1752_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1752_prev;
    }
    
    void gen_01_slide_1752_reset() {
        this->gen_01_slide_1752_prev = 0;
    }
    
    number gen_01_slide_1757_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1757_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1757_prev = this->gen_01_slide_1757_prev + ((x > this->gen_01_slide_1757_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1757_prev;
    }
    
    void gen_01_slide_1757_reset() {
        this->gen_01_slide_1757_prev = 0;
    }
    
    number gen_01_latch_1763_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1763_value = x;
        }
    
        return this->gen_01_latch_1763_value;
    }
    
    void gen_01_latch_1763_dspsetup() {
        this->gen_01_latch_1763_reset();
    }
    
    void gen_01_latch_1763_init() {
        this->gen_01_latch_1763_reset();
    }
    
    void gen_01_latch_1763_reset() {
        this->gen_01_latch_1763_value = 0;
    }
    
    number gen_01_slide_1781_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1781_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1781_prev = this->gen_01_slide_1781_prev + ((x > this->gen_01_slide_1781_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1781_prev;
    }
    
    void gen_01_slide_1781_reset() {
        this->gen_01_slide_1781_prev = 0;
    }
    
    void gen_01_noise_1783_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1783_state
        );
    }
    
    void gen_01_noise_1783_init() {
        this->gen_01_noise_1783_reset();
    }
    
    void gen_01_noise_1783_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1783_state);
    }
    
    number gen_01_noise_1783_next() {
        return xoshiro_next(this->gen_01_noise_1783_state);
    }
    
    number gen_01_slide_1792_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1792_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1792_prev = this->gen_01_slide_1792_prev + ((x > this->gen_01_slide_1792_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1792_prev;
    }
    
    void gen_01_slide_1792_reset() {
        this->gen_01_slide_1792_prev = 0;
    }
    
    number gen_01_phasor_1794_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1794_conv;
    
        if (this->gen_01_phasor_1794_currentPhase < 0.)
            this->gen_01_phasor_1794_currentPhase = 1. + this->gen_01_phasor_1794_currentPhase;
    
        if (this->gen_01_phasor_1794_currentPhase > 1.)
            this->gen_01_phasor_1794_currentPhase = this->gen_01_phasor_1794_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1794_currentPhase;
        this->gen_01_phasor_1794_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1794_reset() {
        this->gen_01_phasor_1794_currentPhase = 0;
    }
    
    void gen_01_phasor_1794_dspsetup() {
        this->gen_01_phasor_1794_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1796_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1796_prev);
        this->gen_01_delta_1796_prev = x;
        return temp;
    }
    
    void gen_01_delta_1796_dspsetup() {
        this->gen_01_delta_1796_reset();
    }
    
    void gen_01_delta_1796_reset() {
        this->gen_01_delta_1796_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1799_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1799_count = 0;
            this->gen_01_counter_1799_carry = 0;
        } else {
            this->gen_01_counter_1799_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1799_count >= limit) || (a < 0 && this->gen_01_counter_1799_count <= limit)) {
                    this->gen_01_counter_1799_count = 0;
                    this->gen_01_counter_1799_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1799_count,
            carry_flag,
            this->gen_01_counter_1799_carry
        };
    }
    
    void gen_01_counter_1799_init() {
        this->gen_01_counter_1799_count = 0;
    }
    
    void gen_01_counter_1799_reset() {
        this->gen_01_counter_1799_carry = 0;
        this->gen_01_counter_1799_count = 0;
    }
    
    number gen_01_delta_1802_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1802_prev);
        this->gen_01_delta_1802_prev = x;
        return temp;
    }
    
    void gen_01_delta_1802_dspsetup() {
        this->gen_01_delta_1802_reset();
    }
    
    void gen_01_delta_1802_reset() {
        this->gen_01_delta_1802_prev = 0;
    }
    
    number gen_01_latch_1806_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1806_value = x;
        }
    
        return this->gen_01_latch_1806_value;
    }
    
    void gen_01_latch_1806_dspsetup() {
        this->gen_01_latch_1806_reset();
    }
    
    void gen_01_latch_1806_init() {
        this->gen_01_latch_1806_reset();
    }
    
    void gen_01_latch_1806_reset() {
        this->gen_01_latch_1806_value = 0;
    }
    
    number gen_01_latch_1808_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1808_value = x;
        }
    
        return this->gen_01_latch_1808_value;
    }
    
    void gen_01_latch_1808_dspsetup() {
        this->gen_01_latch_1808_reset();
    }
    
    void gen_01_latch_1808_init() {
        this->gen_01_latch_1808_reset();
    }
    
    void gen_01_latch_1808_reset() {
        this->gen_01_latch_1808_value = 0;
    }
    
    array<number, 3> gen_01_counter_1816_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1816_count = 0;
            this->gen_01_counter_1816_carry = 0;
        } else {
            this->gen_01_counter_1816_count += a;
        }
    
        return {
            this->gen_01_counter_1816_count,
            carry_flag,
            this->gen_01_counter_1816_carry
        };
    }
    
    void gen_01_counter_1816_init() {
        this->gen_01_counter_1816_count = 0;
    }
    
    void gen_01_counter_1816_reset() {
        this->gen_01_counter_1816_carry = 0;
        this->gen_01_counter_1816_count = 0;
    }
    
    void gen_01_noise_1825_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1825_state
        );
    }
    
    void gen_01_noise_1825_init() {
        this->gen_01_noise_1825_reset();
    }
    
    void gen_01_noise_1825_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1825_state);
    }
    
    number gen_01_noise_1825_next() {
        return xoshiro_next(this->gen_01_noise_1825_state);
    }
    
    void gen_01_noise_1827_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1827_state
        );
    }
    
    void gen_01_noise_1827_init() {
        this->gen_01_noise_1827_reset();
    }
    
    void gen_01_noise_1827_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1827_state);
    }
    
    number gen_01_noise_1827_next() {
        return xoshiro_next(this->gen_01_noise_1827_state);
    }
    
    number gen_01_slide_1831_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1831_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1831_prev = this->gen_01_slide_1831_prev + ((x > this->gen_01_slide_1831_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1831_prev;
    }
    
    void gen_01_slide_1831_reset() {
        this->gen_01_slide_1831_prev = 0;
    }
    
    number gen_01_slide_1841_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1841_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1841_prev = this->gen_01_slide_1841_prev + ((x > this->gen_01_slide_1841_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1841_prev;
    }
    
    void gen_01_slide_1841_reset() {
        this->gen_01_slide_1841_prev = 0;
    }
    
    number gen_01_latch_1844_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1844_value = x;
        }
    
        return this->gen_01_latch_1844_value;
    }
    
    void gen_01_latch_1844_dspsetup() {
        this->gen_01_latch_1844_reset();
    }
    
    void gen_01_latch_1844_init() {
        this->gen_01_latch_1844_reset();
    }
    
    void gen_01_latch_1844_reset() {
        this->gen_01_latch_1844_value = 0;
    }
    
    number gen_01_slide_1847_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1847_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1847_prev = this->gen_01_slide_1847_prev + ((x > this->gen_01_slide_1847_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1847_prev;
    }
    
    void gen_01_slide_1847_reset() {
        this->gen_01_slide_1847_prev = 0;
    }
    
    number gen_01_slide_1852_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1852_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1852_prev = this->gen_01_slide_1852_prev + ((x > this->gen_01_slide_1852_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1852_prev;
    }
    
    void gen_01_slide_1852_reset() {
        this->gen_01_slide_1852_prev = 0;
    }
    
    number gen_01_latch_1858_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1858_value = x;
        }
    
        return this->gen_01_latch_1858_value;
    }
    
    void gen_01_latch_1858_dspsetup() {
        this->gen_01_latch_1858_reset();
    }
    
    void gen_01_latch_1858_init() {
        this->gen_01_latch_1858_reset();
    }
    
    void gen_01_latch_1858_reset() {
        this->gen_01_latch_1858_value = 0;
    }
    
    number gen_01_slide_1876_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1876_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1876_prev = this->gen_01_slide_1876_prev + ((x > this->gen_01_slide_1876_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1876_prev;
    }
    
    void gen_01_slide_1876_reset() {
        this->gen_01_slide_1876_prev = 0;
    }
    
    void gen_01_noise_1878_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1878_state
        );
    }
    
    void gen_01_noise_1878_init() {
        this->gen_01_noise_1878_reset();
    }
    
    void gen_01_noise_1878_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1878_state);
    }
    
    number gen_01_noise_1878_next() {
        return xoshiro_next(this->gen_01_noise_1878_state);
    }
    
    number gen_01_slide_1887_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1887_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1887_prev = this->gen_01_slide_1887_prev + ((x > this->gen_01_slide_1887_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1887_prev;
    }
    
    void gen_01_slide_1887_reset() {
        this->gen_01_slide_1887_prev = 0;
    }
    
    number gen_01_phasor_1889_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1889_conv;
    
        if (this->gen_01_phasor_1889_currentPhase < 0.)
            this->gen_01_phasor_1889_currentPhase = 1. + this->gen_01_phasor_1889_currentPhase;
    
        if (this->gen_01_phasor_1889_currentPhase > 1.)
            this->gen_01_phasor_1889_currentPhase = this->gen_01_phasor_1889_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1889_currentPhase;
        this->gen_01_phasor_1889_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1889_reset() {
        this->gen_01_phasor_1889_currentPhase = 0;
    }
    
    void gen_01_phasor_1889_dspsetup() {
        this->gen_01_phasor_1889_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1891_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1891_prev);
        this->gen_01_delta_1891_prev = x;
        return temp;
    }
    
    void gen_01_delta_1891_dspsetup() {
        this->gen_01_delta_1891_reset();
    }
    
    void gen_01_delta_1891_reset() {
        this->gen_01_delta_1891_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1894_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1894_count = 0;
            this->gen_01_counter_1894_carry = 0;
        } else {
            this->gen_01_counter_1894_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1894_count >= limit) || (a < 0 && this->gen_01_counter_1894_count <= limit)) {
                    this->gen_01_counter_1894_count = 0;
                    this->gen_01_counter_1894_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1894_count,
            carry_flag,
            this->gen_01_counter_1894_carry
        };
    }
    
    void gen_01_counter_1894_init() {
        this->gen_01_counter_1894_count = 0;
    }
    
    void gen_01_counter_1894_reset() {
        this->gen_01_counter_1894_carry = 0;
        this->gen_01_counter_1894_count = 0;
    }
    
    number gen_01_delta_1897_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1897_prev);
        this->gen_01_delta_1897_prev = x;
        return temp;
    }
    
    void gen_01_delta_1897_dspsetup() {
        this->gen_01_delta_1897_reset();
    }
    
    void gen_01_delta_1897_reset() {
        this->gen_01_delta_1897_prev = 0;
    }
    
    number gen_01_latch_1901_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1901_value = x;
        }
    
        return this->gen_01_latch_1901_value;
    }
    
    void gen_01_latch_1901_dspsetup() {
        this->gen_01_latch_1901_reset();
    }
    
    void gen_01_latch_1901_init() {
        this->gen_01_latch_1901_reset();
    }
    
    void gen_01_latch_1901_reset() {
        this->gen_01_latch_1901_value = 0;
    }
    
    number gen_01_latch_1903_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1903_value = x;
        }
    
        return this->gen_01_latch_1903_value;
    }
    
    void gen_01_latch_1903_dspsetup() {
        this->gen_01_latch_1903_reset();
    }
    
    void gen_01_latch_1903_init() {
        this->gen_01_latch_1903_reset();
    }
    
    void gen_01_latch_1903_reset() {
        this->gen_01_latch_1903_value = 0;
    }
    
    array<number, 3> gen_01_counter_1911_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1911_count = 0;
            this->gen_01_counter_1911_carry = 0;
        } else {
            this->gen_01_counter_1911_count += a;
        }
    
        return {
            this->gen_01_counter_1911_count,
            carry_flag,
            this->gen_01_counter_1911_carry
        };
    }
    
    void gen_01_counter_1911_init() {
        this->gen_01_counter_1911_count = 0;
    }
    
    void gen_01_counter_1911_reset() {
        this->gen_01_counter_1911_carry = 0;
        this->gen_01_counter_1911_count = 0;
    }
    
    void gen_01_noise_1920_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1920_state
        );
    }
    
    void gen_01_noise_1920_init() {
        this->gen_01_noise_1920_reset();
    }
    
    void gen_01_noise_1920_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1920_state);
    }
    
    number gen_01_noise_1920_next() {
        return xoshiro_next(this->gen_01_noise_1920_state);
    }
    
    void gen_01_noise_1922_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1922_state
        );
    }
    
    void gen_01_noise_1922_init() {
        this->gen_01_noise_1922_reset();
    }
    
    void gen_01_noise_1922_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1922_state);
    }
    
    number gen_01_noise_1922_next() {
        return xoshiro_next(this->gen_01_noise_1922_state);
    }
    
    number gen_01_slide_1926_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1926_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1926_prev = this->gen_01_slide_1926_prev + ((x > this->gen_01_slide_1926_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1926_prev;
    }
    
    void gen_01_slide_1926_reset() {
        this->gen_01_slide_1926_prev = 0;
    }
    
    number gen_01_slide_1936_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1936_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1936_prev = this->gen_01_slide_1936_prev + ((x > this->gen_01_slide_1936_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1936_prev;
    }
    
    void gen_01_slide_1936_reset() {
        this->gen_01_slide_1936_prev = 0;
    }
    
    number gen_01_latch_1939_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1939_value = x;
        }
    
        return this->gen_01_latch_1939_value;
    }
    
    void gen_01_latch_1939_dspsetup() {
        this->gen_01_latch_1939_reset();
    }
    
    void gen_01_latch_1939_init() {
        this->gen_01_latch_1939_reset();
    }
    
    void gen_01_latch_1939_reset() {
        this->gen_01_latch_1939_value = 0;
    }
    
    number gen_01_slide_1943_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1943_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1943_prev = this->gen_01_slide_1943_prev + ((x > this->gen_01_slide_1943_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1943_prev;
    }
    
    void gen_01_slide_1943_reset() {
        this->gen_01_slide_1943_prev = 0;
    }
    
    number gen_01_slide_1948_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1948_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1948_prev = this->gen_01_slide_1948_prev + ((x > this->gen_01_slide_1948_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1948_prev;
    }
    
    void gen_01_slide_1948_reset() {
        this->gen_01_slide_1948_prev = 0;
    }
    
    number gen_01_latch_1954_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1954_value = x;
        }
    
        return this->gen_01_latch_1954_value;
    }
    
    void gen_01_latch_1954_dspsetup() {
        this->gen_01_latch_1954_reset();
    }
    
    void gen_01_latch_1954_init() {
        this->gen_01_latch_1954_reset();
    }
    
    void gen_01_latch_1954_reset() {
        this->gen_01_latch_1954_value = 0;
    }
    
    number gen_01_slide_1972_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1972_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1972_prev = this->gen_01_slide_1972_prev + ((x > this->gen_01_slide_1972_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1972_prev;
    }
    
    void gen_01_slide_1972_reset() {
        this->gen_01_slide_1972_prev = 0;
    }
    
    void gen_01_noise_1975_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_1975_state
        );
    }
    
    void gen_01_noise_1975_init() {
        this->gen_01_noise_1975_reset();
    }
    
    void gen_01_noise_1975_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_1975_state);
    }
    
    number gen_01_noise_1975_next() {
        return xoshiro_next(this->gen_01_noise_1975_state);
    }
    
    number gen_01_slide_1981_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_1981_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_1981_prev = this->gen_01_slide_1981_prev + ((x > this->gen_01_slide_1981_prev ? iup : idown)) * temp;
        return this->gen_01_slide_1981_prev;
    }
    
    void gen_01_slide_1981_reset() {
        this->gen_01_slide_1981_prev = 0;
    }
    
    number gen_01_phasor_1984_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_1984_conv;
    
        if (this->gen_01_phasor_1984_currentPhase < 0.)
            this->gen_01_phasor_1984_currentPhase = 1. + this->gen_01_phasor_1984_currentPhase;
    
        if (this->gen_01_phasor_1984_currentPhase > 1.)
            this->gen_01_phasor_1984_currentPhase = this->gen_01_phasor_1984_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_1984_currentPhase;
        this->gen_01_phasor_1984_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_1984_reset() {
        this->gen_01_phasor_1984_currentPhase = 0;
    }
    
    void gen_01_phasor_1984_dspsetup() {
        this->gen_01_phasor_1984_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_1986_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1986_prev);
        this->gen_01_delta_1986_prev = x;
        return temp;
    }
    
    void gen_01_delta_1986_dspsetup() {
        this->gen_01_delta_1986_reset();
    }
    
    void gen_01_delta_1986_reset() {
        this->gen_01_delta_1986_prev = 0;
    }
    
    array<number, 3> gen_01_counter_1989_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_1989_count = 0;
            this->gen_01_counter_1989_carry = 0;
        } else {
            this->gen_01_counter_1989_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_1989_count >= limit) || (a < 0 && this->gen_01_counter_1989_count <= limit)) {
                    this->gen_01_counter_1989_count = 0;
                    this->gen_01_counter_1989_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_1989_count,
            carry_flag,
            this->gen_01_counter_1989_carry
        };
    }
    
    void gen_01_counter_1989_init() {
        this->gen_01_counter_1989_count = 0;
    }
    
    void gen_01_counter_1989_reset() {
        this->gen_01_counter_1989_carry = 0;
        this->gen_01_counter_1989_count = 0;
    }
    
    number gen_01_delta_1992_next(number x) {
        number temp = (number)(x - this->gen_01_delta_1992_prev);
        this->gen_01_delta_1992_prev = x;
        return temp;
    }
    
    void gen_01_delta_1992_dspsetup() {
        this->gen_01_delta_1992_reset();
    }
    
    void gen_01_delta_1992_reset() {
        this->gen_01_delta_1992_prev = 0;
    }
    
    number gen_01_latch_1996_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1996_value = x;
        }
    
        return this->gen_01_latch_1996_value;
    }
    
    void gen_01_latch_1996_dspsetup() {
        this->gen_01_latch_1996_reset();
    }
    
    void gen_01_latch_1996_init() {
        this->gen_01_latch_1996_reset();
    }
    
    void gen_01_latch_1996_reset() {
        this->gen_01_latch_1996_value = 0;
    }
    
    number gen_01_latch_1998_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_1998_value = x;
        }
    
        return this->gen_01_latch_1998_value;
    }
    
    void gen_01_latch_1998_dspsetup() {
        this->gen_01_latch_1998_reset();
    }
    
    void gen_01_latch_1998_init() {
        this->gen_01_latch_1998_reset();
    }
    
    void gen_01_latch_1998_reset() {
        this->gen_01_latch_1998_value = 0;
    }
    
    array<number, 3> gen_01_counter_2006_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2006_count = 0;
            this->gen_01_counter_2006_carry = 0;
        } else {
            this->gen_01_counter_2006_count += a;
        }
    
        return {
            this->gen_01_counter_2006_count,
            carry_flag,
            this->gen_01_counter_2006_carry
        };
    }
    
    void gen_01_counter_2006_init() {
        this->gen_01_counter_2006_count = 0;
    }
    
    void gen_01_counter_2006_reset() {
        this->gen_01_counter_2006_carry = 0;
        this->gen_01_counter_2006_count = 0;
    }
    
    void gen_01_noise_2018_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2018_state
        );
    }
    
    void gen_01_noise_2018_init() {
        this->gen_01_noise_2018_reset();
    }
    
    void gen_01_noise_2018_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2018_state);
    }
    
    number gen_01_noise_2018_next() {
        return xoshiro_next(this->gen_01_noise_2018_state);
    }
    
    void gen_01_noise_2020_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2020_state
        );
    }
    
    void gen_01_noise_2020_init() {
        this->gen_01_noise_2020_reset();
    }
    
    void gen_01_noise_2020_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2020_state);
    }
    
    number gen_01_noise_2020_next() {
        return xoshiro_next(this->gen_01_noise_2020_state);
    }
    
    number gen_01_slide_2025_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2025_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2025_prev = this->gen_01_slide_2025_prev + ((x > this->gen_01_slide_2025_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2025_prev;
    }
    
    void gen_01_slide_2025_reset() {
        this->gen_01_slide_2025_prev = 0;
    }
    
    number gen_01_slide_2035_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2035_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2035_prev = this->gen_01_slide_2035_prev + ((x > this->gen_01_slide_2035_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2035_prev;
    }
    
    void gen_01_slide_2035_reset() {
        this->gen_01_slide_2035_prev = 0;
    }
    
    number gen_01_latch_2038_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2038_value = x;
        }
    
        return this->gen_01_latch_2038_value;
    }
    
    void gen_01_latch_2038_dspsetup() {
        this->gen_01_latch_2038_reset();
    }
    
    void gen_01_latch_2038_init() {
        this->gen_01_latch_2038_reset();
    }
    
    void gen_01_latch_2038_reset() {
        this->gen_01_latch_2038_value = 0;
    }
    
    number gen_01_slide_2041_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2041_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2041_prev = this->gen_01_slide_2041_prev + ((x > this->gen_01_slide_2041_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2041_prev;
    }
    
    void gen_01_slide_2041_reset() {
        this->gen_01_slide_2041_prev = 0;
    }
    
    number gen_01_slide_2046_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2046_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2046_prev = this->gen_01_slide_2046_prev + ((x > this->gen_01_slide_2046_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2046_prev;
    }
    
    void gen_01_slide_2046_reset() {
        this->gen_01_slide_2046_prev = 0;
    }
    
    number gen_01_latch_2052_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2052_value = x;
        }
    
        return this->gen_01_latch_2052_value;
    }
    
    void gen_01_latch_2052_dspsetup() {
        this->gen_01_latch_2052_reset();
    }
    
    void gen_01_latch_2052_init() {
        this->gen_01_latch_2052_reset();
    }
    
    void gen_01_latch_2052_reset() {
        this->gen_01_latch_2052_value = 0;
    }
    
    number gen_01_slide_2070_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2070_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2070_prev = this->gen_01_slide_2070_prev + ((x > this->gen_01_slide_2070_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2070_prev;
    }
    
    void gen_01_slide_2070_reset() {
        this->gen_01_slide_2070_prev = 0;
    }
    
    void gen_01_noise_2072_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2072_state
        );
    }
    
    void gen_01_noise_2072_init() {
        this->gen_01_noise_2072_reset();
    }
    
    void gen_01_noise_2072_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2072_state);
    }
    
    number gen_01_noise_2072_next() {
        return xoshiro_next(this->gen_01_noise_2072_state);
    }
    
    number gen_01_slide_2078_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2078_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2078_prev = this->gen_01_slide_2078_prev + ((x > this->gen_01_slide_2078_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2078_prev;
    }
    
    void gen_01_slide_2078_reset() {
        this->gen_01_slide_2078_prev = 0;
    }
    
    number gen_01_phasor_2080_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2080_conv;
    
        if (this->gen_01_phasor_2080_currentPhase < 0.)
            this->gen_01_phasor_2080_currentPhase = 1. + this->gen_01_phasor_2080_currentPhase;
    
        if (this->gen_01_phasor_2080_currentPhase > 1.)
            this->gen_01_phasor_2080_currentPhase = this->gen_01_phasor_2080_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2080_currentPhase;
        this->gen_01_phasor_2080_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2080_reset() {
        this->gen_01_phasor_2080_currentPhase = 0;
    }
    
    void gen_01_phasor_2080_dspsetup() {
        this->gen_01_phasor_2080_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2082_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2082_prev);
        this->gen_01_delta_2082_prev = x;
        return temp;
    }
    
    void gen_01_delta_2082_dspsetup() {
        this->gen_01_delta_2082_reset();
    }
    
    void gen_01_delta_2082_reset() {
        this->gen_01_delta_2082_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2086_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2086_count = 0;
            this->gen_01_counter_2086_carry = 0;
        } else {
            this->gen_01_counter_2086_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2086_count >= limit) || (a < 0 && this->gen_01_counter_2086_count <= limit)) {
                    this->gen_01_counter_2086_count = 0;
                    this->gen_01_counter_2086_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2086_count,
            carry_flag,
            this->gen_01_counter_2086_carry
        };
    }
    
    void gen_01_counter_2086_init() {
        this->gen_01_counter_2086_count = 0;
    }
    
    void gen_01_counter_2086_reset() {
        this->gen_01_counter_2086_carry = 0;
        this->gen_01_counter_2086_count = 0;
    }
    
    number gen_01_delta_2089_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2089_prev);
        this->gen_01_delta_2089_prev = x;
        return temp;
    }
    
    void gen_01_delta_2089_dspsetup() {
        this->gen_01_delta_2089_reset();
    }
    
    void gen_01_delta_2089_reset() {
        this->gen_01_delta_2089_prev = 0;
    }
    
    number gen_01_latch_2093_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2093_value = x;
        }
    
        return this->gen_01_latch_2093_value;
    }
    
    void gen_01_latch_2093_dspsetup() {
        this->gen_01_latch_2093_reset();
    }
    
    void gen_01_latch_2093_init() {
        this->gen_01_latch_2093_reset();
    }
    
    void gen_01_latch_2093_reset() {
        this->gen_01_latch_2093_value = 0;
    }
    
    number gen_01_latch_2095_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2095_value = x;
        }
    
        return this->gen_01_latch_2095_value;
    }
    
    void gen_01_latch_2095_dspsetup() {
        this->gen_01_latch_2095_reset();
    }
    
    void gen_01_latch_2095_init() {
        this->gen_01_latch_2095_reset();
    }
    
    void gen_01_latch_2095_reset() {
        this->gen_01_latch_2095_value = 0;
    }
    
    array<number, 3> gen_01_counter_2103_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2103_count = 0;
            this->gen_01_counter_2103_carry = 0;
        } else {
            this->gen_01_counter_2103_count += a;
        }
    
        return {
            this->gen_01_counter_2103_count,
            carry_flag,
            this->gen_01_counter_2103_carry
        };
    }
    
    void gen_01_counter_2103_init() {
        this->gen_01_counter_2103_count = 0;
    }
    
    void gen_01_counter_2103_reset() {
        this->gen_01_counter_2103_carry = 0;
        this->gen_01_counter_2103_count = 0;
    }
    
    void gen_01_noise_2115_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2115_state
        );
    }
    
    void gen_01_noise_2115_init() {
        this->gen_01_noise_2115_reset();
    }
    
    void gen_01_noise_2115_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2115_state);
    }
    
    number gen_01_noise_2115_next() {
        return xoshiro_next(this->gen_01_noise_2115_state);
    }
    
    void gen_01_noise_2117_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2117_state
        );
    }
    
    void gen_01_noise_2117_init() {
        this->gen_01_noise_2117_reset();
    }
    
    void gen_01_noise_2117_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2117_state);
    }
    
    number gen_01_noise_2117_next() {
        return xoshiro_next(this->gen_01_noise_2117_state);
    }
    
    number gen_01_slide_2121_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2121_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2121_prev = this->gen_01_slide_2121_prev + ((x > this->gen_01_slide_2121_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2121_prev;
    }
    
    void gen_01_slide_2121_reset() {
        this->gen_01_slide_2121_prev = 0;
    }
    
    number gen_01_slide_2131_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2131_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2131_prev = this->gen_01_slide_2131_prev + ((x > this->gen_01_slide_2131_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2131_prev;
    }
    
    void gen_01_slide_2131_reset() {
        this->gen_01_slide_2131_prev = 0;
    }
    
    number gen_01_latch_2134_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2134_value = x;
        }
    
        return this->gen_01_latch_2134_value;
    }
    
    void gen_01_latch_2134_dspsetup() {
        this->gen_01_latch_2134_reset();
    }
    
    void gen_01_latch_2134_init() {
        this->gen_01_latch_2134_reset();
    }
    
    void gen_01_latch_2134_reset() {
        this->gen_01_latch_2134_value = 0;
    }
    
    number gen_01_slide_2138_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2138_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2138_prev = this->gen_01_slide_2138_prev + ((x > this->gen_01_slide_2138_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2138_prev;
    }
    
    void gen_01_slide_2138_reset() {
        this->gen_01_slide_2138_prev = 0;
    }
    
    number gen_01_slide_2143_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2143_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2143_prev = this->gen_01_slide_2143_prev + ((x > this->gen_01_slide_2143_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2143_prev;
    }
    
    void gen_01_slide_2143_reset() {
        this->gen_01_slide_2143_prev = 0;
    }
    
    number gen_01_latch_2149_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2149_value = x;
        }
    
        return this->gen_01_latch_2149_value;
    }
    
    void gen_01_latch_2149_dspsetup() {
        this->gen_01_latch_2149_reset();
    }
    
    void gen_01_latch_2149_init() {
        this->gen_01_latch_2149_reset();
    }
    
    void gen_01_latch_2149_reset() {
        this->gen_01_latch_2149_value = 0;
    }
    
    number gen_01_slide_2167_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2167_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2167_prev = this->gen_01_slide_2167_prev + ((x > this->gen_01_slide_2167_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2167_prev;
    }
    
    void gen_01_slide_2167_reset() {
        this->gen_01_slide_2167_prev = 0;
    }
    
    void gen_01_noise_2169_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2169_state
        );
    }
    
    void gen_01_noise_2169_init() {
        this->gen_01_noise_2169_reset();
    }
    
    void gen_01_noise_2169_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2169_state);
    }
    
    number gen_01_noise_2169_next() {
        return xoshiro_next(this->gen_01_noise_2169_state);
    }
    
    number gen_01_slide_2178_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2178_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2178_prev = this->gen_01_slide_2178_prev + ((x > this->gen_01_slide_2178_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2178_prev;
    }
    
    void gen_01_slide_2178_reset() {
        this->gen_01_slide_2178_prev = 0;
    }
    
    number gen_01_phasor_2180_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2180_conv;
    
        if (this->gen_01_phasor_2180_currentPhase < 0.)
            this->gen_01_phasor_2180_currentPhase = 1. + this->gen_01_phasor_2180_currentPhase;
    
        if (this->gen_01_phasor_2180_currentPhase > 1.)
            this->gen_01_phasor_2180_currentPhase = this->gen_01_phasor_2180_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2180_currentPhase;
        this->gen_01_phasor_2180_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2180_reset() {
        this->gen_01_phasor_2180_currentPhase = 0;
    }
    
    void gen_01_phasor_2180_dspsetup() {
        this->gen_01_phasor_2180_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2182_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2182_prev);
        this->gen_01_delta_2182_prev = x;
        return temp;
    }
    
    void gen_01_delta_2182_dspsetup() {
        this->gen_01_delta_2182_reset();
    }
    
    void gen_01_delta_2182_reset() {
        this->gen_01_delta_2182_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2185_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2185_count = 0;
            this->gen_01_counter_2185_carry = 0;
        } else {
            this->gen_01_counter_2185_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2185_count >= limit) || (a < 0 && this->gen_01_counter_2185_count <= limit)) {
                    this->gen_01_counter_2185_count = 0;
                    this->gen_01_counter_2185_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2185_count,
            carry_flag,
            this->gen_01_counter_2185_carry
        };
    }
    
    void gen_01_counter_2185_init() {
        this->gen_01_counter_2185_count = 0;
    }
    
    void gen_01_counter_2185_reset() {
        this->gen_01_counter_2185_carry = 0;
        this->gen_01_counter_2185_count = 0;
    }
    
    number gen_01_delta_2188_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2188_prev);
        this->gen_01_delta_2188_prev = x;
        return temp;
    }
    
    void gen_01_delta_2188_dspsetup() {
        this->gen_01_delta_2188_reset();
    }
    
    void gen_01_delta_2188_reset() {
        this->gen_01_delta_2188_prev = 0;
    }
    
    number gen_01_latch_2192_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2192_value = x;
        }
    
        return this->gen_01_latch_2192_value;
    }
    
    void gen_01_latch_2192_dspsetup() {
        this->gen_01_latch_2192_reset();
    }
    
    void gen_01_latch_2192_init() {
        this->gen_01_latch_2192_reset();
    }
    
    void gen_01_latch_2192_reset() {
        this->gen_01_latch_2192_value = 0;
    }
    
    number gen_01_latch_2194_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2194_value = x;
        }
    
        return this->gen_01_latch_2194_value;
    }
    
    void gen_01_latch_2194_dspsetup() {
        this->gen_01_latch_2194_reset();
    }
    
    void gen_01_latch_2194_init() {
        this->gen_01_latch_2194_reset();
    }
    
    void gen_01_latch_2194_reset() {
        this->gen_01_latch_2194_value = 0;
    }
    
    array<number, 3> gen_01_counter_2202_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2202_count = 0;
            this->gen_01_counter_2202_carry = 0;
        } else {
            this->gen_01_counter_2202_count += a;
        }
    
        return {
            this->gen_01_counter_2202_count,
            carry_flag,
            this->gen_01_counter_2202_carry
        };
    }
    
    void gen_01_counter_2202_init() {
        this->gen_01_counter_2202_count = 0;
    }
    
    void gen_01_counter_2202_reset() {
        this->gen_01_counter_2202_carry = 0;
        this->gen_01_counter_2202_count = 0;
    }
    
    void gen_01_noise_2211_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2211_state
        );
    }
    
    void gen_01_noise_2211_init() {
        this->gen_01_noise_2211_reset();
    }
    
    void gen_01_noise_2211_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2211_state);
    }
    
    number gen_01_noise_2211_next() {
        return xoshiro_next(this->gen_01_noise_2211_state);
    }
    
    void gen_01_noise_2213_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2213_state
        );
    }
    
    void gen_01_noise_2213_init() {
        this->gen_01_noise_2213_reset();
    }
    
    void gen_01_noise_2213_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2213_state);
    }
    
    number gen_01_noise_2213_next() {
        return xoshiro_next(this->gen_01_noise_2213_state);
    }
    
    number gen_01_slide_2217_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2217_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2217_prev = this->gen_01_slide_2217_prev + ((x > this->gen_01_slide_2217_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2217_prev;
    }
    
    void gen_01_slide_2217_reset() {
        this->gen_01_slide_2217_prev = 0;
    }
    
    number gen_01_slide_2227_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2227_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2227_prev = this->gen_01_slide_2227_prev + ((x > this->gen_01_slide_2227_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2227_prev;
    }
    
    void gen_01_slide_2227_reset() {
        this->gen_01_slide_2227_prev = 0;
    }
    
    number gen_01_latch_2230_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2230_value = x;
        }
    
        return this->gen_01_latch_2230_value;
    }
    
    void gen_01_latch_2230_dspsetup() {
        this->gen_01_latch_2230_reset();
    }
    
    void gen_01_latch_2230_init() {
        this->gen_01_latch_2230_reset();
    }
    
    void gen_01_latch_2230_reset() {
        this->gen_01_latch_2230_value = 0;
    }
    
    number gen_01_slide_2233_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2233_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2233_prev = this->gen_01_slide_2233_prev + ((x > this->gen_01_slide_2233_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2233_prev;
    }
    
    void gen_01_slide_2233_reset() {
        this->gen_01_slide_2233_prev = 0;
    }
    
    number gen_01_slide_2238_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2238_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2238_prev = this->gen_01_slide_2238_prev + ((x > this->gen_01_slide_2238_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2238_prev;
    }
    
    void gen_01_slide_2238_reset() {
        this->gen_01_slide_2238_prev = 0;
    }
    
    number gen_01_latch_2244_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2244_value = x;
        }
    
        return this->gen_01_latch_2244_value;
    }
    
    void gen_01_latch_2244_dspsetup() {
        this->gen_01_latch_2244_reset();
    }
    
    void gen_01_latch_2244_init() {
        this->gen_01_latch_2244_reset();
    }
    
    void gen_01_latch_2244_reset() {
        this->gen_01_latch_2244_value = 0;
    }
    
    number gen_01_slide_2262_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2262_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2262_prev = this->gen_01_slide_2262_prev + ((x > this->gen_01_slide_2262_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2262_prev;
    }
    
    void gen_01_slide_2262_reset() {
        this->gen_01_slide_2262_prev = 0;
    }
    
    void gen_01_noise_2264_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2264_state
        );
    }
    
    void gen_01_noise_2264_init() {
        this->gen_01_noise_2264_reset();
    }
    
    void gen_01_noise_2264_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2264_state);
    }
    
    number gen_01_noise_2264_next() {
        return xoshiro_next(this->gen_01_noise_2264_state);
    }
    
    number gen_01_slide_2273_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2273_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2273_prev = this->gen_01_slide_2273_prev + ((x > this->gen_01_slide_2273_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2273_prev;
    }
    
    void gen_01_slide_2273_reset() {
        this->gen_01_slide_2273_prev = 0;
    }
    
    number gen_01_phasor_2275_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2275_conv;
    
        if (this->gen_01_phasor_2275_currentPhase < 0.)
            this->gen_01_phasor_2275_currentPhase = 1. + this->gen_01_phasor_2275_currentPhase;
    
        if (this->gen_01_phasor_2275_currentPhase > 1.)
            this->gen_01_phasor_2275_currentPhase = this->gen_01_phasor_2275_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2275_currentPhase;
        this->gen_01_phasor_2275_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2275_reset() {
        this->gen_01_phasor_2275_currentPhase = 0;
    }
    
    void gen_01_phasor_2275_dspsetup() {
        this->gen_01_phasor_2275_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2277_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2277_prev);
        this->gen_01_delta_2277_prev = x;
        return temp;
    }
    
    void gen_01_delta_2277_dspsetup() {
        this->gen_01_delta_2277_reset();
    }
    
    void gen_01_delta_2277_reset() {
        this->gen_01_delta_2277_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2280_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2280_count = 0;
            this->gen_01_counter_2280_carry = 0;
        } else {
            this->gen_01_counter_2280_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2280_count >= limit) || (a < 0 && this->gen_01_counter_2280_count <= limit)) {
                    this->gen_01_counter_2280_count = 0;
                    this->gen_01_counter_2280_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2280_count,
            carry_flag,
            this->gen_01_counter_2280_carry
        };
    }
    
    void gen_01_counter_2280_init() {
        this->gen_01_counter_2280_count = 0;
    }
    
    void gen_01_counter_2280_reset() {
        this->gen_01_counter_2280_carry = 0;
        this->gen_01_counter_2280_count = 0;
    }
    
    number gen_01_delta_2283_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2283_prev);
        this->gen_01_delta_2283_prev = x;
        return temp;
    }
    
    void gen_01_delta_2283_dspsetup() {
        this->gen_01_delta_2283_reset();
    }
    
    void gen_01_delta_2283_reset() {
        this->gen_01_delta_2283_prev = 0;
    }
    
    number gen_01_latch_2287_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2287_value = x;
        }
    
        return this->gen_01_latch_2287_value;
    }
    
    void gen_01_latch_2287_dspsetup() {
        this->gen_01_latch_2287_reset();
    }
    
    void gen_01_latch_2287_init() {
        this->gen_01_latch_2287_reset();
    }
    
    void gen_01_latch_2287_reset() {
        this->gen_01_latch_2287_value = 0;
    }
    
    number gen_01_latch_2289_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2289_value = x;
        }
    
        return this->gen_01_latch_2289_value;
    }
    
    void gen_01_latch_2289_dspsetup() {
        this->gen_01_latch_2289_reset();
    }
    
    void gen_01_latch_2289_init() {
        this->gen_01_latch_2289_reset();
    }
    
    void gen_01_latch_2289_reset() {
        this->gen_01_latch_2289_value = 0;
    }
    
    array<number, 3> gen_01_counter_2297_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2297_count = 0;
            this->gen_01_counter_2297_carry = 0;
        } else {
            this->gen_01_counter_2297_count += a;
        }
    
        return {
            this->gen_01_counter_2297_count,
            carry_flag,
            this->gen_01_counter_2297_carry
        };
    }
    
    void gen_01_counter_2297_init() {
        this->gen_01_counter_2297_count = 0;
    }
    
    void gen_01_counter_2297_reset() {
        this->gen_01_counter_2297_carry = 0;
        this->gen_01_counter_2297_count = 0;
    }
    
    void gen_01_noise_2306_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2306_state
        );
    }
    
    void gen_01_noise_2306_init() {
        this->gen_01_noise_2306_reset();
    }
    
    void gen_01_noise_2306_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2306_state);
    }
    
    number gen_01_noise_2306_next() {
        return xoshiro_next(this->gen_01_noise_2306_state);
    }
    
    void gen_01_noise_2308_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2308_state
        );
    }
    
    void gen_01_noise_2308_init() {
        this->gen_01_noise_2308_reset();
    }
    
    void gen_01_noise_2308_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2308_state);
    }
    
    number gen_01_noise_2308_next() {
        return xoshiro_next(this->gen_01_noise_2308_state);
    }
    
    number gen_01_slide_2312_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2312_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2312_prev = this->gen_01_slide_2312_prev + ((x > this->gen_01_slide_2312_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2312_prev;
    }
    
    void gen_01_slide_2312_reset() {
        this->gen_01_slide_2312_prev = 0;
    }
    
    number gen_01_slide_2322_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2322_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2322_prev = this->gen_01_slide_2322_prev + ((x > this->gen_01_slide_2322_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2322_prev;
    }
    
    void gen_01_slide_2322_reset() {
        this->gen_01_slide_2322_prev = 0;
    }
    
    number gen_01_latch_2325_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2325_value = x;
        }
    
        return this->gen_01_latch_2325_value;
    }
    
    void gen_01_latch_2325_dspsetup() {
        this->gen_01_latch_2325_reset();
    }
    
    void gen_01_latch_2325_init() {
        this->gen_01_latch_2325_reset();
    }
    
    void gen_01_latch_2325_reset() {
        this->gen_01_latch_2325_value = 0;
    }
    
    number gen_01_slide_2328_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2328_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2328_prev = this->gen_01_slide_2328_prev + ((x > this->gen_01_slide_2328_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2328_prev;
    }
    
    void gen_01_slide_2328_reset() {
        this->gen_01_slide_2328_prev = 0;
    }
    
    number gen_01_slide_2333_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2333_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2333_prev = this->gen_01_slide_2333_prev + ((x > this->gen_01_slide_2333_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2333_prev;
    }
    
    void gen_01_slide_2333_reset() {
        this->gen_01_slide_2333_prev = 0;
    }
    
    number gen_01_latch_2339_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2339_value = x;
        }
    
        return this->gen_01_latch_2339_value;
    }
    
    void gen_01_latch_2339_dspsetup() {
        this->gen_01_latch_2339_reset();
    }
    
    void gen_01_latch_2339_init() {
        this->gen_01_latch_2339_reset();
    }
    
    void gen_01_latch_2339_reset() {
        this->gen_01_latch_2339_value = 0;
    }
    
    number gen_01_slide_2357_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2357_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2357_prev = this->gen_01_slide_2357_prev + ((x > this->gen_01_slide_2357_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2357_prev;
    }
    
    void gen_01_slide_2357_reset() {
        this->gen_01_slide_2357_prev = 0;
    }
    
    void gen_01_noise_2359_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2359_state
        );
    }
    
    void gen_01_noise_2359_init() {
        this->gen_01_noise_2359_reset();
    }
    
    void gen_01_noise_2359_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2359_state);
    }
    
    number gen_01_noise_2359_next() {
        return xoshiro_next(this->gen_01_noise_2359_state);
    }
    
    number gen_01_slide_2368_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2368_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2368_prev = this->gen_01_slide_2368_prev + ((x > this->gen_01_slide_2368_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2368_prev;
    }
    
    void gen_01_slide_2368_reset() {
        this->gen_01_slide_2368_prev = 0;
    }
    
    number gen_01_phasor_2370_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2370_conv;
    
        if (this->gen_01_phasor_2370_currentPhase < 0.)
            this->gen_01_phasor_2370_currentPhase = 1. + this->gen_01_phasor_2370_currentPhase;
    
        if (this->gen_01_phasor_2370_currentPhase > 1.)
            this->gen_01_phasor_2370_currentPhase = this->gen_01_phasor_2370_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2370_currentPhase;
        this->gen_01_phasor_2370_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2370_reset() {
        this->gen_01_phasor_2370_currentPhase = 0;
    }
    
    void gen_01_phasor_2370_dspsetup() {
        this->gen_01_phasor_2370_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2372_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2372_prev);
        this->gen_01_delta_2372_prev = x;
        return temp;
    }
    
    void gen_01_delta_2372_dspsetup() {
        this->gen_01_delta_2372_reset();
    }
    
    void gen_01_delta_2372_reset() {
        this->gen_01_delta_2372_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2375_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2375_count = 0;
            this->gen_01_counter_2375_carry = 0;
        } else {
            this->gen_01_counter_2375_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2375_count >= limit) || (a < 0 && this->gen_01_counter_2375_count <= limit)) {
                    this->gen_01_counter_2375_count = 0;
                    this->gen_01_counter_2375_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2375_count,
            carry_flag,
            this->gen_01_counter_2375_carry
        };
    }
    
    void gen_01_counter_2375_init() {
        this->gen_01_counter_2375_count = 0;
    }
    
    void gen_01_counter_2375_reset() {
        this->gen_01_counter_2375_carry = 0;
        this->gen_01_counter_2375_count = 0;
    }
    
    number gen_01_delta_2378_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2378_prev);
        this->gen_01_delta_2378_prev = x;
        return temp;
    }
    
    void gen_01_delta_2378_dspsetup() {
        this->gen_01_delta_2378_reset();
    }
    
    void gen_01_delta_2378_reset() {
        this->gen_01_delta_2378_prev = 0;
    }
    
    number gen_01_latch_2382_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2382_value = x;
        }
    
        return this->gen_01_latch_2382_value;
    }
    
    void gen_01_latch_2382_dspsetup() {
        this->gen_01_latch_2382_reset();
    }
    
    void gen_01_latch_2382_init() {
        this->gen_01_latch_2382_reset();
    }
    
    void gen_01_latch_2382_reset() {
        this->gen_01_latch_2382_value = 0;
    }
    
    number gen_01_latch_2384_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2384_value = x;
        }
    
        return this->gen_01_latch_2384_value;
    }
    
    void gen_01_latch_2384_dspsetup() {
        this->gen_01_latch_2384_reset();
    }
    
    void gen_01_latch_2384_init() {
        this->gen_01_latch_2384_reset();
    }
    
    void gen_01_latch_2384_reset() {
        this->gen_01_latch_2384_value = 0;
    }
    
    array<number, 3> gen_01_counter_2392_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2392_count = 0;
            this->gen_01_counter_2392_carry = 0;
        } else {
            this->gen_01_counter_2392_count += a;
        }
    
        return {
            this->gen_01_counter_2392_count,
            carry_flag,
            this->gen_01_counter_2392_carry
        };
    }
    
    void gen_01_counter_2392_init() {
        this->gen_01_counter_2392_count = 0;
    }
    
    void gen_01_counter_2392_reset() {
        this->gen_01_counter_2392_carry = 0;
        this->gen_01_counter_2392_count = 0;
    }
    
    void gen_01_noise_2401_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2401_state
        );
    }
    
    void gen_01_noise_2401_init() {
        this->gen_01_noise_2401_reset();
    }
    
    void gen_01_noise_2401_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2401_state);
    }
    
    number gen_01_noise_2401_next() {
        return xoshiro_next(this->gen_01_noise_2401_state);
    }
    
    void gen_01_noise_2403_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2403_state
        );
    }
    
    void gen_01_noise_2403_init() {
        this->gen_01_noise_2403_reset();
    }
    
    void gen_01_noise_2403_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2403_state);
    }
    
    number gen_01_noise_2403_next() {
        return xoshiro_next(this->gen_01_noise_2403_state);
    }
    
    number gen_01_slide_2407_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2407_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2407_prev = this->gen_01_slide_2407_prev + ((x > this->gen_01_slide_2407_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2407_prev;
    }
    
    void gen_01_slide_2407_reset() {
        this->gen_01_slide_2407_prev = 0;
    }
    
    number gen_01_slide_2417_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2417_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2417_prev = this->gen_01_slide_2417_prev + ((x > this->gen_01_slide_2417_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2417_prev;
    }
    
    void gen_01_slide_2417_reset() {
        this->gen_01_slide_2417_prev = 0;
    }
    
    number gen_01_latch_2420_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2420_value = x;
        }
    
        return this->gen_01_latch_2420_value;
    }
    
    void gen_01_latch_2420_dspsetup() {
        this->gen_01_latch_2420_reset();
    }
    
    void gen_01_latch_2420_init() {
        this->gen_01_latch_2420_reset();
    }
    
    void gen_01_latch_2420_reset() {
        this->gen_01_latch_2420_value = 0;
    }
    
    number gen_01_slide_2423_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2423_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2423_prev = this->gen_01_slide_2423_prev + ((x > this->gen_01_slide_2423_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2423_prev;
    }
    
    void gen_01_slide_2423_reset() {
        this->gen_01_slide_2423_prev = 0;
    }
    
    number gen_01_slide_2428_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2428_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2428_prev = this->gen_01_slide_2428_prev + ((x > this->gen_01_slide_2428_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2428_prev;
    }
    
    void gen_01_slide_2428_reset() {
        this->gen_01_slide_2428_prev = 0;
    }
    
    number gen_01_latch_2434_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2434_value = x;
        }
    
        return this->gen_01_latch_2434_value;
    }
    
    void gen_01_latch_2434_dspsetup() {
        this->gen_01_latch_2434_reset();
    }
    
    void gen_01_latch_2434_init() {
        this->gen_01_latch_2434_reset();
    }
    
    void gen_01_latch_2434_reset() {
        this->gen_01_latch_2434_value = 0;
    }
    
    number gen_01_slide_2452_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2452_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2452_prev = this->gen_01_slide_2452_prev + ((x > this->gen_01_slide_2452_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2452_prev;
    }
    
    void gen_01_slide_2452_reset() {
        this->gen_01_slide_2452_prev = 0;
    }
    
    void gen_01_noise_2454_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2454_state
        );
    }
    
    void gen_01_noise_2454_init() {
        this->gen_01_noise_2454_reset();
    }
    
    void gen_01_noise_2454_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2454_state);
    }
    
    number gen_01_noise_2454_next() {
        return xoshiro_next(this->gen_01_noise_2454_state);
    }
    
    number gen_01_slide_2463_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2463_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2463_prev = this->gen_01_slide_2463_prev + ((x > this->gen_01_slide_2463_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2463_prev;
    }
    
    void gen_01_slide_2463_reset() {
        this->gen_01_slide_2463_prev = 0;
    }
    
    number gen_01_phasor_2465_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2465_conv;
    
        if (this->gen_01_phasor_2465_currentPhase < 0.)
            this->gen_01_phasor_2465_currentPhase = 1. + this->gen_01_phasor_2465_currentPhase;
    
        if (this->gen_01_phasor_2465_currentPhase > 1.)
            this->gen_01_phasor_2465_currentPhase = this->gen_01_phasor_2465_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2465_currentPhase;
        this->gen_01_phasor_2465_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2465_reset() {
        this->gen_01_phasor_2465_currentPhase = 0;
    }
    
    void gen_01_phasor_2465_dspsetup() {
        this->gen_01_phasor_2465_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2467_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2467_prev);
        this->gen_01_delta_2467_prev = x;
        return temp;
    }
    
    void gen_01_delta_2467_dspsetup() {
        this->gen_01_delta_2467_reset();
    }
    
    void gen_01_delta_2467_reset() {
        this->gen_01_delta_2467_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2470_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2470_count = 0;
            this->gen_01_counter_2470_carry = 0;
        } else {
            this->gen_01_counter_2470_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2470_count >= limit) || (a < 0 && this->gen_01_counter_2470_count <= limit)) {
                    this->gen_01_counter_2470_count = 0;
                    this->gen_01_counter_2470_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2470_count,
            carry_flag,
            this->gen_01_counter_2470_carry
        };
    }
    
    void gen_01_counter_2470_init() {
        this->gen_01_counter_2470_count = 0;
    }
    
    void gen_01_counter_2470_reset() {
        this->gen_01_counter_2470_carry = 0;
        this->gen_01_counter_2470_count = 0;
    }
    
    number gen_01_delta_2473_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2473_prev);
        this->gen_01_delta_2473_prev = x;
        return temp;
    }
    
    void gen_01_delta_2473_dspsetup() {
        this->gen_01_delta_2473_reset();
    }
    
    void gen_01_delta_2473_reset() {
        this->gen_01_delta_2473_prev = 0;
    }
    
    number gen_01_latch_2477_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2477_value = x;
        }
    
        return this->gen_01_latch_2477_value;
    }
    
    void gen_01_latch_2477_dspsetup() {
        this->gen_01_latch_2477_reset();
    }
    
    void gen_01_latch_2477_init() {
        this->gen_01_latch_2477_reset();
    }
    
    void gen_01_latch_2477_reset() {
        this->gen_01_latch_2477_value = 0;
    }
    
    number gen_01_latch_2486_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2486_value = x;
        }
    
        return this->gen_01_latch_2486_value;
    }
    
    void gen_01_latch_2486_dspsetup() {
        this->gen_01_latch_2486_reset();
    }
    
    void gen_01_latch_2486_init() {
        this->gen_01_latch_2486_reset();
    }
    
    void gen_01_latch_2486_reset() {
        this->gen_01_latch_2486_value = 0;
    }
    
    array<number, 3> gen_01_counter_2488_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2488_count = 0;
            this->gen_01_counter_2488_carry = 0;
        } else {
            this->gen_01_counter_2488_count += a;
        }
    
        return {
            this->gen_01_counter_2488_count,
            carry_flag,
            this->gen_01_counter_2488_carry
        };
    }
    
    void gen_01_counter_2488_init() {
        this->gen_01_counter_2488_count = 0;
    }
    
    void gen_01_counter_2488_reset() {
        this->gen_01_counter_2488_carry = 0;
        this->gen_01_counter_2488_count = 0;
    }
    
    void gen_01_noise_2497_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2497_state
        );
    }
    
    void gen_01_noise_2497_init() {
        this->gen_01_noise_2497_reset();
    }
    
    void gen_01_noise_2497_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2497_state);
    }
    
    number gen_01_noise_2497_next() {
        return xoshiro_next(this->gen_01_noise_2497_state);
    }
    
    void gen_01_noise_2499_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2499_state
        );
    }
    
    void gen_01_noise_2499_init() {
        this->gen_01_noise_2499_reset();
    }
    
    void gen_01_noise_2499_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2499_state);
    }
    
    number gen_01_noise_2499_next() {
        return xoshiro_next(this->gen_01_noise_2499_state);
    }
    
    number gen_01_slide_2503_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2503_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2503_prev = this->gen_01_slide_2503_prev + ((x > this->gen_01_slide_2503_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2503_prev;
    }
    
    void gen_01_slide_2503_reset() {
        this->gen_01_slide_2503_prev = 0;
    }
    
    number gen_01_slide_2513_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2513_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2513_prev = this->gen_01_slide_2513_prev + ((x > this->gen_01_slide_2513_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2513_prev;
    }
    
    void gen_01_slide_2513_reset() {
        this->gen_01_slide_2513_prev = 0;
    }
    
    number gen_01_latch_2516_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2516_value = x;
        }
    
        return this->gen_01_latch_2516_value;
    }
    
    void gen_01_latch_2516_dspsetup() {
        this->gen_01_latch_2516_reset();
    }
    
    void gen_01_latch_2516_init() {
        this->gen_01_latch_2516_reset();
    }
    
    void gen_01_latch_2516_reset() {
        this->gen_01_latch_2516_value = 0;
    }
    
    number gen_01_slide_2519_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2519_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2519_prev = this->gen_01_slide_2519_prev + ((x > this->gen_01_slide_2519_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2519_prev;
    }
    
    void gen_01_slide_2519_reset() {
        this->gen_01_slide_2519_prev = 0;
    }
    
    number gen_01_slide_2525_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2525_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2525_prev = this->gen_01_slide_2525_prev + ((x > this->gen_01_slide_2525_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2525_prev;
    }
    
    void gen_01_slide_2525_reset() {
        this->gen_01_slide_2525_prev = 0;
    }
    
    number gen_01_latch_2531_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2531_value = x;
        }
    
        return this->gen_01_latch_2531_value;
    }
    
    void gen_01_latch_2531_dspsetup() {
        this->gen_01_latch_2531_reset();
    }
    
    void gen_01_latch_2531_init() {
        this->gen_01_latch_2531_reset();
    }
    
    void gen_01_latch_2531_reset() {
        this->gen_01_latch_2531_value = 0;
    }
    
    number gen_01_slide_2549_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2549_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2549_prev = this->gen_01_slide_2549_prev + ((x > this->gen_01_slide_2549_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2549_prev;
    }
    
    void gen_01_slide_2549_reset() {
        this->gen_01_slide_2549_prev = 0;
    }
    
    void gen_01_noise_2551_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2551_state
        );
    }
    
    void gen_01_noise_2551_init() {
        this->gen_01_noise_2551_reset();
    }
    
    void gen_01_noise_2551_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2551_state);
    }
    
    number gen_01_noise_2551_next() {
        return xoshiro_next(this->gen_01_noise_2551_state);
    }
    
    number gen_01_slide_2560_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2560_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2560_prev = this->gen_01_slide_2560_prev + ((x > this->gen_01_slide_2560_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2560_prev;
    }
    
    void gen_01_slide_2560_reset() {
        this->gen_01_slide_2560_prev = 0;
    }
    
    number gen_01_phasor_2562_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2562_conv;
    
        if (this->gen_01_phasor_2562_currentPhase < 0.)
            this->gen_01_phasor_2562_currentPhase = 1. + this->gen_01_phasor_2562_currentPhase;
    
        if (this->gen_01_phasor_2562_currentPhase > 1.)
            this->gen_01_phasor_2562_currentPhase = this->gen_01_phasor_2562_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2562_currentPhase;
        this->gen_01_phasor_2562_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2562_reset() {
        this->gen_01_phasor_2562_currentPhase = 0;
    }
    
    void gen_01_phasor_2562_dspsetup() {
        this->gen_01_phasor_2562_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2564_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2564_prev);
        this->gen_01_delta_2564_prev = x;
        return temp;
    }
    
    void gen_01_delta_2564_dspsetup() {
        this->gen_01_delta_2564_reset();
    }
    
    void gen_01_delta_2564_reset() {
        this->gen_01_delta_2564_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2567_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2567_count = 0;
            this->gen_01_counter_2567_carry = 0;
        } else {
            this->gen_01_counter_2567_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2567_count >= limit) || (a < 0 && this->gen_01_counter_2567_count <= limit)) {
                    this->gen_01_counter_2567_count = 0;
                    this->gen_01_counter_2567_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2567_count,
            carry_flag,
            this->gen_01_counter_2567_carry
        };
    }
    
    void gen_01_counter_2567_init() {
        this->gen_01_counter_2567_count = 0;
    }
    
    void gen_01_counter_2567_reset() {
        this->gen_01_counter_2567_carry = 0;
        this->gen_01_counter_2567_count = 0;
    }
    
    number gen_01_delta_2570_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2570_prev);
        this->gen_01_delta_2570_prev = x;
        return temp;
    }
    
    void gen_01_delta_2570_dspsetup() {
        this->gen_01_delta_2570_reset();
    }
    
    void gen_01_delta_2570_reset() {
        this->gen_01_delta_2570_prev = 0;
    }
    
    number gen_01_latch_2574_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2574_value = x;
        }
    
        return this->gen_01_latch_2574_value;
    }
    
    void gen_01_latch_2574_dspsetup() {
        this->gen_01_latch_2574_reset();
    }
    
    void gen_01_latch_2574_init() {
        this->gen_01_latch_2574_reset();
    }
    
    void gen_01_latch_2574_reset() {
        this->gen_01_latch_2574_value = 0;
    }
    
    number gen_01_latch_2582_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2582_value = x;
        }
    
        return this->gen_01_latch_2582_value;
    }
    
    void gen_01_latch_2582_dspsetup() {
        this->gen_01_latch_2582_reset();
    }
    
    void gen_01_latch_2582_init() {
        this->gen_01_latch_2582_reset();
    }
    
    void gen_01_latch_2582_reset() {
        this->gen_01_latch_2582_value = 0;
    }
    
    array<number, 3> gen_01_counter_2584_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2584_count = 0;
            this->gen_01_counter_2584_carry = 0;
        } else {
            this->gen_01_counter_2584_count += a;
        }
    
        return {
            this->gen_01_counter_2584_count,
            carry_flag,
            this->gen_01_counter_2584_carry
        };
    }
    
    void gen_01_counter_2584_init() {
        this->gen_01_counter_2584_count = 0;
    }
    
    void gen_01_counter_2584_reset() {
        this->gen_01_counter_2584_carry = 0;
        this->gen_01_counter_2584_count = 0;
    }
    
    void gen_01_noise_2593_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2593_state
        );
    }
    
    void gen_01_noise_2593_init() {
        this->gen_01_noise_2593_reset();
    }
    
    void gen_01_noise_2593_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2593_state);
    }
    
    number gen_01_noise_2593_next() {
        return xoshiro_next(this->gen_01_noise_2593_state);
    }
    
    void gen_01_noise_2595_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2595_state
        );
    }
    
    void gen_01_noise_2595_init() {
        this->gen_01_noise_2595_reset();
    }
    
    void gen_01_noise_2595_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2595_state);
    }
    
    number gen_01_noise_2595_next() {
        return xoshiro_next(this->gen_01_noise_2595_state);
    }
    
    number gen_01_slide_2599_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2599_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2599_prev = this->gen_01_slide_2599_prev + ((x > this->gen_01_slide_2599_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2599_prev;
    }
    
    void gen_01_slide_2599_reset() {
        this->gen_01_slide_2599_prev = 0;
    }
    
    number gen_01_slide_2609_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2609_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2609_prev = this->gen_01_slide_2609_prev + ((x > this->gen_01_slide_2609_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2609_prev;
    }
    
    void gen_01_slide_2609_reset() {
        this->gen_01_slide_2609_prev = 0;
    }
    
    number gen_01_latch_2612_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2612_value = x;
        }
    
        return this->gen_01_latch_2612_value;
    }
    
    void gen_01_latch_2612_dspsetup() {
        this->gen_01_latch_2612_reset();
    }
    
    void gen_01_latch_2612_init() {
        this->gen_01_latch_2612_reset();
    }
    
    void gen_01_latch_2612_reset() {
        this->gen_01_latch_2612_value = 0;
    }
    
    number gen_01_slide_2615_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2615_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2615_prev = this->gen_01_slide_2615_prev + ((x > this->gen_01_slide_2615_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2615_prev;
    }
    
    void gen_01_slide_2615_reset() {
        this->gen_01_slide_2615_prev = 0;
    }
    
    number gen_01_slide_2620_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2620_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2620_prev = this->gen_01_slide_2620_prev + ((x > this->gen_01_slide_2620_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2620_prev;
    }
    
    void gen_01_slide_2620_reset() {
        this->gen_01_slide_2620_prev = 0;
    }
    
    number gen_01_latch_2626_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2626_value = x;
        }
    
        return this->gen_01_latch_2626_value;
    }
    
    void gen_01_latch_2626_dspsetup() {
        this->gen_01_latch_2626_reset();
    }
    
    void gen_01_latch_2626_init() {
        this->gen_01_latch_2626_reset();
    }
    
    void gen_01_latch_2626_reset() {
        this->gen_01_latch_2626_value = 0;
    }
    
    number gen_01_slide_2644_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2644_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2644_prev = this->gen_01_slide_2644_prev + ((x > this->gen_01_slide_2644_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2644_prev;
    }
    
    void gen_01_slide_2644_reset() {
        this->gen_01_slide_2644_prev = 0;
    }
    
    void gen_01_noise_2646_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2646_state
        );
    }
    
    void gen_01_noise_2646_init() {
        this->gen_01_noise_2646_reset();
    }
    
    void gen_01_noise_2646_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2646_state);
    }
    
    number gen_01_noise_2646_next() {
        return xoshiro_next(this->gen_01_noise_2646_state);
    }
    
    number gen_01_slide_2652_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2652_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2652_prev = this->gen_01_slide_2652_prev + ((x > this->gen_01_slide_2652_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2652_prev;
    }
    
    void gen_01_slide_2652_reset() {
        this->gen_01_slide_2652_prev = 0;
    }
    
    number gen_01_phasor_2654_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2654_conv;
    
        if (this->gen_01_phasor_2654_currentPhase < 0.)
            this->gen_01_phasor_2654_currentPhase = 1. + this->gen_01_phasor_2654_currentPhase;
    
        if (this->gen_01_phasor_2654_currentPhase > 1.)
            this->gen_01_phasor_2654_currentPhase = this->gen_01_phasor_2654_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2654_currentPhase;
        this->gen_01_phasor_2654_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2654_reset() {
        this->gen_01_phasor_2654_currentPhase = 0;
    }
    
    void gen_01_phasor_2654_dspsetup() {
        this->gen_01_phasor_2654_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2656_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2656_prev);
        this->gen_01_delta_2656_prev = x;
        return temp;
    }
    
    void gen_01_delta_2656_dspsetup() {
        this->gen_01_delta_2656_reset();
    }
    
    void gen_01_delta_2656_reset() {
        this->gen_01_delta_2656_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2660_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2660_count = 0;
            this->gen_01_counter_2660_carry = 0;
        } else {
            this->gen_01_counter_2660_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2660_count >= limit) || (a < 0 && this->gen_01_counter_2660_count <= limit)) {
                    this->gen_01_counter_2660_count = 0;
                    this->gen_01_counter_2660_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2660_count,
            carry_flag,
            this->gen_01_counter_2660_carry
        };
    }
    
    void gen_01_counter_2660_init() {
        this->gen_01_counter_2660_count = 0;
    }
    
    void gen_01_counter_2660_reset() {
        this->gen_01_counter_2660_carry = 0;
        this->gen_01_counter_2660_count = 0;
    }
    
    number gen_01_delta_2663_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2663_prev);
        this->gen_01_delta_2663_prev = x;
        return temp;
    }
    
    void gen_01_delta_2663_dspsetup() {
        this->gen_01_delta_2663_reset();
    }
    
    void gen_01_delta_2663_reset() {
        this->gen_01_delta_2663_prev = 0;
    }
    
    number gen_01_latch_2667_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2667_value = x;
        }
    
        return this->gen_01_latch_2667_value;
    }
    
    void gen_01_latch_2667_dspsetup() {
        this->gen_01_latch_2667_reset();
    }
    
    void gen_01_latch_2667_init() {
        this->gen_01_latch_2667_reset();
    }
    
    void gen_01_latch_2667_reset() {
        this->gen_01_latch_2667_value = 0;
    }
    
    number gen_01_latch_2669_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2669_value = x;
        }
    
        return this->gen_01_latch_2669_value;
    }
    
    void gen_01_latch_2669_dspsetup() {
        this->gen_01_latch_2669_reset();
    }
    
    void gen_01_latch_2669_init() {
        this->gen_01_latch_2669_reset();
    }
    
    void gen_01_latch_2669_reset() {
        this->gen_01_latch_2669_value = 0;
    }
    
    array<number, 3> gen_01_counter_2677_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2677_count = 0;
            this->gen_01_counter_2677_carry = 0;
        } else {
            this->gen_01_counter_2677_count += a;
        }
    
        return {
            this->gen_01_counter_2677_count,
            carry_flag,
            this->gen_01_counter_2677_carry
        };
    }
    
    void gen_01_counter_2677_init() {
        this->gen_01_counter_2677_count = 0;
    }
    
    void gen_01_counter_2677_reset() {
        this->gen_01_counter_2677_carry = 0;
        this->gen_01_counter_2677_count = 0;
    }
    
    void gen_01_noise_2689_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2689_state
        );
    }
    
    void gen_01_noise_2689_init() {
        this->gen_01_noise_2689_reset();
    }
    
    void gen_01_noise_2689_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2689_state);
    }
    
    number gen_01_noise_2689_next() {
        return xoshiro_next(this->gen_01_noise_2689_state);
    }
    
    void gen_01_noise_2691_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2691_state
        );
    }
    
    void gen_01_noise_2691_init() {
        this->gen_01_noise_2691_reset();
    }
    
    void gen_01_noise_2691_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2691_state);
    }
    
    number gen_01_noise_2691_next() {
        return xoshiro_next(this->gen_01_noise_2691_state);
    }
    
    number gen_01_slide_2695_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2695_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2695_prev = this->gen_01_slide_2695_prev + ((x > this->gen_01_slide_2695_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2695_prev;
    }
    
    void gen_01_slide_2695_reset() {
        this->gen_01_slide_2695_prev = 0;
    }
    
    number gen_01_slide_2705_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2705_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2705_prev = this->gen_01_slide_2705_prev + ((x > this->gen_01_slide_2705_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2705_prev;
    }
    
    void gen_01_slide_2705_reset() {
        this->gen_01_slide_2705_prev = 0;
    }
    
    number gen_01_latch_2708_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2708_value = x;
        }
    
        return this->gen_01_latch_2708_value;
    }
    
    void gen_01_latch_2708_dspsetup() {
        this->gen_01_latch_2708_reset();
    }
    
    void gen_01_latch_2708_init() {
        this->gen_01_latch_2708_reset();
    }
    
    void gen_01_latch_2708_reset() {
        this->gen_01_latch_2708_value = 0;
    }
    
    number gen_01_slide_2711_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2711_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2711_prev = this->gen_01_slide_2711_prev + ((x > this->gen_01_slide_2711_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2711_prev;
    }
    
    void gen_01_slide_2711_reset() {
        this->gen_01_slide_2711_prev = 0;
    }
    
    number gen_01_slide_2716_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2716_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2716_prev = this->gen_01_slide_2716_prev + ((x > this->gen_01_slide_2716_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2716_prev;
    }
    
    void gen_01_slide_2716_reset() {
        this->gen_01_slide_2716_prev = 0;
    }
    
    number gen_01_latch_2722_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2722_value = x;
        }
    
        return this->gen_01_latch_2722_value;
    }
    
    void gen_01_latch_2722_dspsetup() {
        this->gen_01_latch_2722_reset();
    }
    
    void gen_01_latch_2722_init() {
        this->gen_01_latch_2722_reset();
    }
    
    void gen_01_latch_2722_reset() {
        this->gen_01_latch_2722_value = 0;
    }
    
    number gen_01_slide_2740_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2740_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2740_prev = this->gen_01_slide_2740_prev + ((x > this->gen_01_slide_2740_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2740_prev;
    }
    
    void gen_01_slide_2740_reset() {
        this->gen_01_slide_2740_prev = 0;
    }
    
    void gen_01_noise_2742_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2742_state
        );
    }
    
    void gen_01_noise_2742_init() {
        this->gen_01_noise_2742_reset();
    }
    
    void gen_01_noise_2742_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2742_state);
    }
    
    number gen_01_noise_2742_next() {
        return xoshiro_next(this->gen_01_noise_2742_state);
    }
    
    number gen_01_slide_2751_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2751_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2751_prev = this->gen_01_slide_2751_prev + ((x > this->gen_01_slide_2751_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2751_prev;
    }
    
    void gen_01_slide_2751_reset() {
        this->gen_01_slide_2751_prev = 0;
    }
    
    number gen_01_phasor_2753_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2753_conv;
    
        if (this->gen_01_phasor_2753_currentPhase < 0.)
            this->gen_01_phasor_2753_currentPhase = 1. + this->gen_01_phasor_2753_currentPhase;
    
        if (this->gen_01_phasor_2753_currentPhase > 1.)
            this->gen_01_phasor_2753_currentPhase = this->gen_01_phasor_2753_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2753_currentPhase;
        this->gen_01_phasor_2753_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2753_reset() {
        this->gen_01_phasor_2753_currentPhase = 0;
    }
    
    void gen_01_phasor_2753_dspsetup() {
        this->gen_01_phasor_2753_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2755_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2755_prev);
        this->gen_01_delta_2755_prev = x;
        return temp;
    }
    
    void gen_01_delta_2755_dspsetup() {
        this->gen_01_delta_2755_reset();
    }
    
    void gen_01_delta_2755_reset() {
        this->gen_01_delta_2755_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2758_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2758_count = 0;
            this->gen_01_counter_2758_carry = 0;
        } else {
            this->gen_01_counter_2758_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2758_count >= limit) || (a < 0 && this->gen_01_counter_2758_count <= limit)) {
                    this->gen_01_counter_2758_count = 0;
                    this->gen_01_counter_2758_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2758_count,
            carry_flag,
            this->gen_01_counter_2758_carry
        };
    }
    
    void gen_01_counter_2758_init() {
        this->gen_01_counter_2758_count = 0;
    }
    
    void gen_01_counter_2758_reset() {
        this->gen_01_counter_2758_carry = 0;
        this->gen_01_counter_2758_count = 0;
    }
    
    number gen_01_delta_2761_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2761_prev);
        this->gen_01_delta_2761_prev = x;
        return temp;
    }
    
    void gen_01_delta_2761_dspsetup() {
        this->gen_01_delta_2761_reset();
    }
    
    void gen_01_delta_2761_reset() {
        this->gen_01_delta_2761_prev = 0;
    }
    
    number gen_01_latch_2765_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2765_value = x;
        }
    
        return this->gen_01_latch_2765_value;
    }
    
    void gen_01_latch_2765_dspsetup() {
        this->gen_01_latch_2765_reset();
    }
    
    void gen_01_latch_2765_init() {
        this->gen_01_latch_2765_reset();
    }
    
    void gen_01_latch_2765_reset() {
        this->gen_01_latch_2765_value = 0;
    }
    
    number gen_01_latch_2773_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2773_value = x;
        }
    
        return this->gen_01_latch_2773_value;
    }
    
    void gen_01_latch_2773_dspsetup() {
        this->gen_01_latch_2773_reset();
    }
    
    void gen_01_latch_2773_init() {
        this->gen_01_latch_2773_reset();
    }
    
    void gen_01_latch_2773_reset() {
        this->gen_01_latch_2773_value = 0;
    }
    
    array<number, 3> gen_01_counter_2775_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2775_count = 0;
            this->gen_01_counter_2775_carry = 0;
        } else {
            this->gen_01_counter_2775_count += a;
        }
    
        return {
            this->gen_01_counter_2775_count,
            carry_flag,
            this->gen_01_counter_2775_carry
        };
    }
    
    void gen_01_counter_2775_init() {
        this->gen_01_counter_2775_count = 0;
    }
    
    void gen_01_counter_2775_reset() {
        this->gen_01_counter_2775_carry = 0;
        this->gen_01_counter_2775_count = 0;
    }
    
    void gen_01_noise_2784_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2784_state
        );
    }
    
    void gen_01_noise_2784_init() {
        this->gen_01_noise_2784_reset();
    }
    
    void gen_01_noise_2784_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2784_state);
    }
    
    number gen_01_noise_2784_next() {
        return xoshiro_next(this->gen_01_noise_2784_state);
    }
    
    void gen_01_noise_2786_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2786_state
        );
    }
    
    void gen_01_noise_2786_init() {
        this->gen_01_noise_2786_reset();
    }
    
    void gen_01_noise_2786_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2786_state);
    }
    
    number gen_01_noise_2786_next() {
        return xoshiro_next(this->gen_01_noise_2786_state);
    }
    
    number gen_01_slide_2790_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2790_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2790_prev = this->gen_01_slide_2790_prev + ((x > this->gen_01_slide_2790_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2790_prev;
    }
    
    void gen_01_slide_2790_reset() {
        this->gen_01_slide_2790_prev = 0;
    }
    
    number gen_01_slide_2800_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2800_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2800_prev = this->gen_01_slide_2800_prev + ((x > this->gen_01_slide_2800_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2800_prev;
    }
    
    void gen_01_slide_2800_reset() {
        this->gen_01_slide_2800_prev = 0;
    }
    
    number gen_01_latch_2803_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2803_value = x;
        }
    
        return this->gen_01_latch_2803_value;
    }
    
    void gen_01_latch_2803_dspsetup() {
        this->gen_01_latch_2803_reset();
    }
    
    void gen_01_latch_2803_init() {
        this->gen_01_latch_2803_reset();
    }
    
    void gen_01_latch_2803_reset() {
        this->gen_01_latch_2803_value = 0;
    }
    
    number gen_01_slide_2806_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2806_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2806_prev = this->gen_01_slide_2806_prev + ((x > this->gen_01_slide_2806_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2806_prev;
    }
    
    void gen_01_slide_2806_reset() {
        this->gen_01_slide_2806_prev = 0;
    }
    
    number gen_01_slide_2811_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2811_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2811_prev = this->gen_01_slide_2811_prev + ((x > this->gen_01_slide_2811_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2811_prev;
    }
    
    void gen_01_slide_2811_reset() {
        this->gen_01_slide_2811_prev = 0;
    }
    
    number gen_01_latch_2817_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2817_value = x;
        }
    
        return this->gen_01_latch_2817_value;
    }
    
    void gen_01_latch_2817_dspsetup() {
        this->gen_01_latch_2817_reset();
    }
    
    void gen_01_latch_2817_init() {
        this->gen_01_latch_2817_reset();
    }
    
    void gen_01_latch_2817_reset() {
        this->gen_01_latch_2817_value = 0;
    }
    
    number gen_01_slide_2835_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2835_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2835_prev = this->gen_01_slide_2835_prev + ((x > this->gen_01_slide_2835_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2835_prev;
    }
    
    void gen_01_slide_2835_reset() {
        this->gen_01_slide_2835_prev = 0;
    }
    
    void gen_01_noise_2837_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2837_state
        );
    }
    
    void gen_01_noise_2837_init() {
        this->gen_01_noise_2837_reset();
    }
    
    void gen_01_noise_2837_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2837_state);
    }
    
    number gen_01_noise_2837_next() {
        return xoshiro_next(this->gen_01_noise_2837_state);
    }
    
    number gen_01_slide_2846_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2846_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2846_prev = this->gen_01_slide_2846_prev + ((x > this->gen_01_slide_2846_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2846_prev;
    }
    
    void gen_01_slide_2846_reset() {
        this->gen_01_slide_2846_prev = 0;
    }
    
    number gen_01_phasor_2848_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2848_conv;
    
        if (this->gen_01_phasor_2848_currentPhase < 0.)
            this->gen_01_phasor_2848_currentPhase = 1. + this->gen_01_phasor_2848_currentPhase;
    
        if (this->gen_01_phasor_2848_currentPhase > 1.)
            this->gen_01_phasor_2848_currentPhase = this->gen_01_phasor_2848_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2848_currentPhase;
        this->gen_01_phasor_2848_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2848_reset() {
        this->gen_01_phasor_2848_currentPhase = 0;
    }
    
    void gen_01_phasor_2848_dspsetup() {
        this->gen_01_phasor_2848_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2850_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2850_prev);
        this->gen_01_delta_2850_prev = x;
        return temp;
    }
    
    void gen_01_delta_2850_dspsetup() {
        this->gen_01_delta_2850_reset();
    }
    
    void gen_01_delta_2850_reset() {
        this->gen_01_delta_2850_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2853_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2853_count = 0;
            this->gen_01_counter_2853_carry = 0;
        } else {
            this->gen_01_counter_2853_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2853_count >= limit) || (a < 0 && this->gen_01_counter_2853_count <= limit)) {
                    this->gen_01_counter_2853_count = 0;
                    this->gen_01_counter_2853_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2853_count,
            carry_flag,
            this->gen_01_counter_2853_carry
        };
    }
    
    void gen_01_counter_2853_init() {
        this->gen_01_counter_2853_count = 0;
    }
    
    void gen_01_counter_2853_reset() {
        this->gen_01_counter_2853_carry = 0;
        this->gen_01_counter_2853_count = 0;
    }
    
    number gen_01_delta_2856_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2856_prev);
        this->gen_01_delta_2856_prev = x;
        return temp;
    }
    
    void gen_01_delta_2856_dspsetup() {
        this->gen_01_delta_2856_reset();
    }
    
    void gen_01_delta_2856_reset() {
        this->gen_01_delta_2856_prev = 0;
    }
    
    number gen_01_latch_2860_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2860_value = x;
        }
    
        return this->gen_01_latch_2860_value;
    }
    
    void gen_01_latch_2860_dspsetup() {
        this->gen_01_latch_2860_reset();
    }
    
    void gen_01_latch_2860_init() {
        this->gen_01_latch_2860_reset();
    }
    
    void gen_01_latch_2860_reset() {
        this->gen_01_latch_2860_value = 0;
    }
    
    number gen_01_latch_2868_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2868_value = x;
        }
    
        return this->gen_01_latch_2868_value;
    }
    
    void gen_01_latch_2868_dspsetup() {
        this->gen_01_latch_2868_reset();
    }
    
    void gen_01_latch_2868_init() {
        this->gen_01_latch_2868_reset();
    }
    
    void gen_01_latch_2868_reset() {
        this->gen_01_latch_2868_value = 0;
    }
    
    array<number, 3> gen_01_counter_2870_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2870_count = 0;
            this->gen_01_counter_2870_carry = 0;
        } else {
            this->gen_01_counter_2870_count += a;
        }
    
        return {
            this->gen_01_counter_2870_count,
            carry_flag,
            this->gen_01_counter_2870_carry
        };
    }
    
    void gen_01_counter_2870_init() {
        this->gen_01_counter_2870_count = 0;
    }
    
    void gen_01_counter_2870_reset() {
        this->gen_01_counter_2870_carry = 0;
        this->gen_01_counter_2870_count = 0;
    }
    
    void gen_01_noise_2879_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2879_state
        );
    }
    
    void gen_01_noise_2879_init() {
        this->gen_01_noise_2879_reset();
    }
    
    void gen_01_noise_2879_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2879_state);
    }
    
    number gen_01_noise_2879_next() {
        return xoshiro_next(this->gen_01_noise_2879_state);
    }
    
    void gen_01_noise_2881_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2881_state
        );
    }
    
    void gen_01_noise_2881_init() {
        this->gen_01_noise_2881_reset();
    }
    
    void gen_01_noise_2881_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2881_state);
    }
    
    number gen_01_noise_2881_next() {
        return xoshiro_next(this->gen_01_noise_2881_state);
    }
    
    number gen_01_slide_2885_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2885_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2885_prev = this->gen_01_slide_2885_prev + ((x > this->gen_01_slide_2885_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2885_prev;
    }
    
    void gen_01_slide_2885_reset() {
        this->gen_01_slide_2885_prev = 0;
    }
    
    number gen_01_slide_2895_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2895_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2895_prev = this->gen_01_slide_2895_prev + ((x > this->gen_01_slide_2895_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2895_prev;
    }
    
    void gen_01_slide_2895_reset() {
        this->gen_01_slide_2895_prev = 0;
    }
    
    number gen_01_latch_2898_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2898_value = x;
        }
    
        return this->gen_01_latch_2898_value;
    }
    
    void gen_01_latch_2898_dspsetup() {
        this->gen_01_latch_2898_reset();
    }
    
    void gen_01_latch_2898_init() {
        this->gen_01_latch_2898_reset();
    }
    
    void gen_01_latch_2898_reset() {
        this->gen_01_latch_2898_value = 0;
    }
    
    number gen_01_slide_2901_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2901_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2901_prev = this->gen_01_slide_2901_prev + ((x > this->gen_01_slide_2901_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2901_prev;
    }
    
    void gen_01_slide_2901_reset() {
        this->gen_01_slide_2901_prev = 0;
    }
    
    number gen_01_slide_2906_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2906_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2906_prev = this->gen_01_slide_2906_prev + ((x > this->gen_01_slide_2906_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2906_prev;
    }
    
    void gen_01_slide_2906_reset() {
        this->gen_01_slide_2906_prev = 0;
    }
    
    number gen_01_latch_2912_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2912_value = x;
        }
    
        return this->gen_01_latch_2912_value;
    }
    
    void gen_01_latch_2912_dspsetup() {
        this->gen_01_latch_2912_reset();
    }
    
    void gen_01_latch_2912_init() {
        this->gen_01_latch_2912_reset();
    }
    
    void gen_01_latch_2912_reset() {
        this->gen_01_latch_2912_value = 0;
    }
    
    number gen_01_slide_2930_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2930_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2930_prev = this->gen_01_slide_2930_prev + ((x > this->gen_01_slide_2930_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2930_prev;
    }
    
    void gen_01_slide_2930_reset() {
        this->gen_01_slide_2930_prev = 0;
    }
    
    void gen_01_noise_2932_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2932_state
        );
    }
    
    void gen_01_noise_2932_init() {
        this->gen_01_noise_2932_reset();
    }
    
    void gen_01_noise_2932_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2932_state);
    }
    
    number gen_01_noise_2932_next() {
        return xoshiro_next(this->gen_01_noise_2932_state);
    }
    
    number gen_01_slide_2938_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2938_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2938_prev = this->gen_01_slide_2938_prev + ((x > this->gen_01_slide_2938_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2938_prev;
    }
    
    void gen_01_slide_2938_reset() {
        this->gen_01_slide_2938_prev = 0;
    }
    
    number gen_01_phasor_2940_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_2940_conv;
    
        if (this->gen_01_phasor_2940_currentPhase < 0.)
            this->gen_01_phasor_2940_currentPhase = 1. + this->gen_01_phasor_2940_currentPhase;
    
        if (this->gen_01_phasor_2940_currentPhase > 1.)
            this->gen_01_phasor_2940_currentPhase = this->gen_01_phasor_2940_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_2940_currentPhase;
        this->gen_01_phasor_2940_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_2940_reset() {
        this->gen_01_phasor_2940_currentPhase = 0;
    }
    
    void gen_01_phasor_2940_dspsetup() {
        this->gen_01_phasor_2940_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_2942_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2942_prev);
        this->gen_01_delta_2942_prev = x;
        return temp;
    }
    
    void gen_01_delta_2942_dspsetup() {
        this->gen_01_delta_2942_reset();
    }
    
    void gen_01_delta_2942_reset() {
        this->gen_01_delta_2942_prev = 0;
    }
    
    array<number, 3> gen_01_counter_2945_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2945_count = 0;
            this->gen_01_counter_2945_carry = 0;
        } else {
            this->gen_01_counter_2945_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_2945_count >= limit) || (a < 0 && this->gen_01_counter_2945_count <= limit)) {
                    this->gen_01_counter_2945_count = 0;
                    this->gen_01_counter_2945_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_2945_count,
            carry_flag,
            this->gen_01_counter_2945_carry
        };
    }
    
    void gen_01_counter_2945_init() {
        this->gen_01_counter_2945_count = 0;
    }
    
    void gen_01_counter_2945_reset() {
        this->gen_01_counter_2945_carry = 0;
        this->gen_01_counter_2945_count = 0;
    }
    
    number gen_01_delta_2948_next(number x) {
        number temp = (number)(x - this->gen_01_delta_2948_prev);
        this->gen_01_delta_2948_prev = x;
        return temp;
    }
    
    void gen_01_delta_2948_dspsetup() {
        this->gen_01_delta_2948_reset();
    }
    
    void gen_01_delta_2948_reset() {
        this->gen_01_delta_2948_prev = 0;
    }
    
    number gen_01_latch_2952_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2952_value = x;
        }
    
        return this->gen_01_latch_2952_value;
    }
    
    void gen_01_latch_2952_dspsetup() {
        this->gen_01_latch_2952_reset();
    }
    
    void gen_01_latch_2952_init() {
        this->gen_01_latch_2952_reset();
    }
    
    void gen_01_latch_2952_reset() {
        this->gen_01_latch_2952_value = 0;
    }
    
    number gen_01_latch_2954_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2954_value = x;
        }
    
        return this->gen_01_latch_2954_value;
    }
    
    void gen_01_latch_2954_dspsetup() {
        this->gen_01_latch_2954_reset();
    }
    
    void gen_01_latch_2954_init() {
        this->gen_01_latch_2954_reset();
    }
    
    void gen_01_latch_2954_reset() {
        this->gen_01_latch_2954_value = 0;
    }
    
    array<number, 3> gen_01_counter_2962_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_2962_count = 0;
            this->gen_01_counter_2962_carry = 0;
        } else {
            this->gen_01_counter_2962_count += a;
        }
    
        return {
            this->gen_01_counter_2962_count,
            carry_flag,
            this->gen_01_counter_2962_carry
        };
    }
    
    void gen_01_counter_2962_init() {
        this->gen_01_counter_2962_count = 0;
    }
    
    void gen_01_counter_2962_reset() {
        this->gen_01_counter_2962_carry = 0;
        this->gen_01_counter_2962_count = 0;
    }
    
    void gen_01_noise_2974_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2974_state
        );
    }
    
    void gen_01_noise_2974_init() {
        this->gen_01_noise_2974_reset();
    }
    
    void gen_01_noise_2974_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2974_state);
    }
    
    number gen_01_noise_2974_next() {
        return xoshiro_next(this->gen_01_noise_2974_state);
    }
    
    void gen_01_noise_2976_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_2976_state
        );
    }
    
    void gen_01_noise_2976_init() {
        this->gen_01_noise_2976_reset();
    }
    
    void gen_01_noise_2976_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_2976_state);
    }
    
    number gen_01_noise_2976_next() {
        return xoshiro_next(this->gen_01_noise_2976_state);
    }
    
    number gen_01_slide_2980_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2980_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2980_prev = this->gen_01_slide_2980_prev + ((x > this->gen_01_slide_2980_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2980_prev;
    }
    
    void gen_01_slide_2980_reset() {
        this->gen_01_slide_2980_prev = 0;
    }
    
    number gen_01_slide_2990_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2990_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2990_prev = this->gen_01_slide_2990_prev + ((x > this->gen_01_slide_2990_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2990_prev;
    }
    
    void gen_01_slide_2990_reset() {
        this->gen_01_slide_2990_prev = 0;
    }
    
    number gen_01_latch_2993_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_2993_value = x;
        }
    
        return this->gen_01_latch_2993_value;
    }
    
    void gen_01_latch_2993_dspsetup() {
        this->gen_01_latch_2993_reset();
    }
    
    void gen_01_latch_2993_init() {
        this->gen_01_latch_2993_reset();
    }
    
    void gen_01_latch_2993_reset() {
        this->gen_01_latch_2993_value = 0;
    }
    
    number gen_01_slide_2996_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_2996_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_2996_prev = this->gen_01_slide_2996_prev + ((x > this->gen_01_slide_2996_prev ? iup : idown)) * temp;
        return this->gen_01_slide_2996_prev;
    }
    
    void gen_01_slide_2996_reset() {
        this->gen_01_slide_2996_prev = 0;
    }
    
    number gen_01_slide_3001_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3001_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3001_prev = this->gen_01_slide_3001_prev + ((x > this->gen_01_slide_3001_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3001_prev;
    }
    
    void gen_01_slide_3001_reset() {
        this->gen_01_slide_3001_prev = 0;
    }
    
    number gen_01_latch_3007_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_3007_value = x;
        }
    
        return this->gen_01_latch_3007_value;
    }
    
    void gen_01_latch_3007_dspsetup() {
        this->gen_01_latch_3007_reset();
    }
    
    void gen_01_latch_3007_init() {
        this->gen_01_latch_3007_reset();
    }
    
    void gen_01_latch_3007_reset() {
        this->gen_01_latch_3007_value = 0;
    }
    
    number gen_01_slide_3025_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3025_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3025_prev = this->gen_01_slide_3025_prev + ((x > this->gen_01_slide_3025_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3025_prev;
    }
    
    void gen_01_slide_3025_reset() {
        this->gen_01_slide_3025_prev = 0;
    }
    
    void gen_01_noise_3027_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_3027_state
        );
    }
    
    void gen_01_noise_3027_init() {
        this->gen_01_noise_3027_reset();
    }
    
    void gen_01_noise_3027_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_3027_state);
    }
    
    number gen_01_noise_3027_next() {
        return xoshiro_next(this->gen_01_noise_3027_state);
    }
    
    number gen_01_slide_3036_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3036_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3036_prev = this->gen_01_slide_3036_prev + ((x > this->gen_01_slide_3036_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3036_prev;
    }
    
    void gen_01_slide_3036_reset() {
        this->gen_01_slide_3036_prev = 0;
    }
    
    number gen_01_phasor_3038_next(number freq, number reset) {
        RNBO_UNUSED(reset);
        number pincr = freq * this->gen_01_phasor_3038_conv;
    
        if (this->gen_01_phasor_3038_currentPhase < 0.)
            this->gen_01_phasor_3038_currentPhase = 1. + this->gen_01_phasor_3038_currentPhase;
    
        if (this->gen_01_phasor_3038_currentPhase > 1.)
            this->gen_01_phasor_3038_currentPhase = this->gen_01_phasor_3038_currentPhase - 1.;
    
        number tmp = this->gen_01_phasor_3038_currentPhase;
        this->gen_01_phasor_3038_currentPhase += pincr;
        return tmp;
    }
    
    void gen_01_phasor_3038_reset() {
        this->gen_01_phasor_3038_currentPhase = 0;
    }
    
    void gen_01_phasor_3038_dspsetup() {
        this->gen_01_phasor_3038_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
    }
    
    number gen_01_delta_3040_next(number x) {
        number temp = (number)(x - this->gen_01_delta_3040_prev);
        this->gen_01_delta_3040_prev = x;
        return temp;
    }
    
    void gen_01_delta_3040_dspsetup() {
        this->gen_01_delta_3040_reset();
    }
    
    void gen_01_delta_3040_reset() {
        this->gen_01_delta_3040_prev = 0;
    }
    
    array<number, 3> gen_01_counter_3043_next(number a, number reset, number limit) {
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_3043_count = 0;
            this->gen_01_counter_3043_carry = 0;
        } else {
            this->gen_01_counter_3043_count += a;
    
            if (limit != 0) {
                if ((a > 0 && this->gen_01_counter_3043_count >= limit) || (a < 0 && this->gen_01_counter_3043_count <= limit)) {
                    this->gen_01_counter_3043_count = 0;
                    this->gen_01_counter_3043_carry += 1;
                    carry_flag = 1;
                }
            }
        }
    
        return {
            this->gen_01_counter_3043_count,
            carry_flag,
            this->gen_01_counter_3043_carry
        };
    }
    
    void gen_01_counter_3043_init() {
        this->gen_01_counter_3043_count = 0;
    }
    
    void gen_01_counter_3043_reset() {
        this->gen_01_counter_3043_carry = 0;
        this->gen_01_counter_3043_count = 0;
    }
    
    number gen_01_delta_3046_next(number x) {
        number temp = (number)(x - this->gen_01_delta_3046_prev);
        this->gen_01_delta_3046_prev = x;
        return temp;
    }
    
    void gen_01_delta_3046_dspsetup() {
        this->gen_01_delta_3046_reset();
    }
    
    void gen_01_delta_3046_reset() {
        this->gen_01_delta_3046_prev = 0;
    }
    
    number gen_01_latch_3050_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_3050_value = x;
        }
    
        return this->gen_01_latch_3050_value;
    }
    
    void gen_01_latch_3050_dspsetup() {
        this->gen_01_latch_3050_reset();
    }
    
    void gen_01_latch_3050_init() {
        this->gen_01_latch_3050_reset();
    }
    
    void gen_01_latch_3050_reset() {
        this->gen_01_latch_3050_value = 0;
    }
    
    number gen_01_latch_3058_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_3058_value = x;
        }
    
        return this->gen_01_latch_3058_value;
    }
    
    void gen_01_latch_3058_dspsetup() {
        this->gen_01_latch_3058_reset();
    }
    
    void gen_01_latch_3058_init() {
        this->gen_01_latch_3058_reset();
    }
    
    void gen_01_latch_3058_reset() {
        this->gen_01_latch_3058_value = 0;
    }
    
    array<number, 3> gen_01_counter_3060_next(number a, number reset, number limit) {
        RNBO_UNUSED(limit);
        number carry_flag = 0;
    
        if (reset != 0) {
            this->gen_01_counter_3060_count = 0;
            this->gen_01_counter_3060_carry = 0;
        } else {
            this->gen_01_counter_3060_count += a;
        }
    
        return {
            this->gen_01_counter_3060_count,
            carry_flag,
            this->gen_01_counter_3060_carry
        };
    }
    
    void gen_01_counter_3060_init() {
        this->gen_01_counter_3060_count = 0;
    }
    
    void gen_01_counter_3060_reset() {
        this->gen_01_counter_3060_carry = 0;
        this->gen_01_counter_3060_count = 0;
    }
    
    void gen_01_noise_3069_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_3069_state
        );
    }
    
    void gen_01_noise_3069_init() {
        this->gen_01_noise_3069_reset();
    }
    
    void gen_01_noise_3069_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_3069_state);
    }
    
    number gen_01_noise_3069_next() {
        return xoshiro_next(this->gen_01_noise_3069_state);
    }
    
    void gen_01_noise_3071_reset() {
        xoshiro_reset(
            systemticks() + this->voice() + this->random(0, 10000),
            this->gen_01_noise_3071_state
        );
    }
    
    void gen_01_noise_3071_init() {
        this->gen_01_noise_3071_reset();
    }
    
    void gen_01_noise_3071_seed(number v) {
        xoshiro_reset(v, this->gen_01_noise_3071_state);
    }
    
    number gen_01_noise_3071_next() {
        return xoshiro_next(this->gen_01_noise_3071_state);
    }
    
    number gen_01_slide_3075_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3075_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3075_prev = this->gen_01_slide_3075_prev + ((x > this->gen_01_slide_3075_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3075_prev;
    }
    
    void gen_01_slide_3075_reset() {
        this->gen_01_slide_3075_prev = 0;
    }
    
    number gen_01_slide_3085_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3085_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3085_prev = this->gen_01_slide_3085_prev + ((x > this->gen_01_slide_3085_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3085_prev;
    }
    
    void gen_01_slide_3085_reset() {
        this->gen_01_slide_3085_prev = 0;
    }
    
    number gen_01_latch_3088_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_3088_value = x;
        }
    
        return this->gen_01_latch_3088_value;
    }
    
    void gen_01_latch_3088_dspsetup() {
        this->gen_01_latch_3088_reset();
    }
    
    void gen_01_latch_3088_init() {
        this->gen_01_latch_3088_reset();
    }
    
    void gen_01_latch_3088_reset() {
        this->gen_01_latch_3088_value = 0;
    }
    
    number gen_01_slide_3091_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3091_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3091_prev = this->gen_01_slide_3091_prev + ((x > this->gen_01_slide_3091_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3091_prev;
    }
    
    void gen_01_slide_3091_reset() {
        this->gen_01_slide_3091_prev = 0;
    }
    
    number gen_01_slide_3096_next(number x, number up, number down) {
        number temp = x - this->gen_01_slide_3096_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
        this->gen_01_slide_3096_prev = this->gen_01_slide_3096_prev + ((x > this->gen_01_slide_3096_prev ? iup : idown)) * temp;
        return this->gen_01_slide_3096_prev;
    }
    
    void gen_01_slide_3096_reset() {
        this->gen_01_slide_3096_prev = 0;
    }
    
    number gen_01_latch_3102_next(number x, number control) {
        if (control != 0.) {
            this->gen_01_latch_3102_value = x;
        }
    
        return this->gen_01_latch_3102_value;
    }
    
    void gen_01_latch_3102_dspsetup() {
        this->gen_01_latch_3102_reset();
    }
    
    void gen_01_latch_3102_init() {
        this->gen_01_latch_3102_reset();
    }
    
    void gen_01_latch_3102_reset() {
        this->gen_01_latch_3102_value = 0;
    }
    
    void gen_01_dspsetup(bool force) {
        if ((bool)(this->gen_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->gen_01_setupDone = true;
        this->gen_01_phasor_264_dspsetup();
        this->gen_01_delta_266_dspsetup();
        this->gen_01_delta_272_dspsetup();
        this->gen_01_latch_276_dspsetup();
        this->gen_01_latch_278_dspsetup();
        this->gen_01_latch_314_dspsetup();
        this->gen_01_latch_328_dspsetup();
        this->gen_01_phasor_356_dspsetup();
        this->gen_01_delta_358_dspsetup();
        this->gen_01_delta_364_dspsetup();
        this->gen_01_latch_368_dspsetup();
        this->gen_01_latch_370_dspsetup();
        this->gen_01_latch_409_dspsetup();
        this->gen_01_latch_423_dspsetup();
        this->gen_01_phasor_454_dspsetup();
        this->gen_01_delta_456_dspsetup();
        this->gen_01_delta_462_dspsetup();
        this->gen_01_latch_466_dspsetup();
        this->gen_01_latch_469_dspsetup();
        this->gen_01_latch_505_dspsetup();
        this->gen_01_latch_519_dspsetup();
        this->gen_01_phasor_551_dspsetup();
        this->gen_01_delta_553_dspsetup();
        this->gen_01_delta_559_dspsetup();
        this->gen_01_latch_563_dspsetup();
        this->gen_01_latch_571_dspsetup();
        this->gen_01_latch_601_dspsetup();
        this->gen_01_latch_615_dspsetup();
        this->gen_01_phasor_643_dspsetup();
        this->gen_01_delta_645_dspsetup();
        this->gen_01_delta_651_dspsetup();
        this->gen_01_latch_655_dspsetup();
        this->gen_01_latch_657_dspsetup();
        this->gen_01_latch_696_dspsetup();
        this->gen_01_latch_710_dspsetup();
        this->gen_01_phasor_741_dspsetup();
        this->gen_01_delta_743_dspsetup();
        this->gen_01_delta_749_dspsetup();
        this->gen_01_latch_753_dspsetup();
        this->gen_01_latch_755_dspsetup();
        this->gen_01_latch_791_dspsetup();
        this->gen_01_latch_806_dspsetup();
        this->gen_01_phasor_838_dspsetup();
        this->gen_01_delta_840_dspsetup();
        this->gen_01_delta_846_dspsetup();
        this->gen_01_latch_850_dspsetup();
        this->gen_01_latch_852_dspsetup();
        this->gen_01_latch_888_dspsetup();
        this->gen_01_latch_902_dspsetup();
        this->gen_01_phasor_933_dspsetup();
        this->gen_01_delta_935_dspsetup();
        this->gen_01_delta_941_dspsetup();
        this->gen_01_latch_945_dspsetup();
        this->gen_01_latch_947_dspsetup();
        this->gen_01_latch_983_dspsetup();
        this->gen_01_latch_997_dspsetup();
        this->gen_01_phasor_1025_dspsetup();
        this->gen_01_delta_1027_dspsetup();
        this->gen_01_delta_1033_dspsetup();
        this->gen_01_latch_1037_dspsetup();
        this->gen_01_latch_1039_dspsetup();
        this->gen_01_latch_1078_dspsetup();
        this->gen_01_latch_1092_dspsetup();
        this->gen_01_phasor_1123_dspsetup();
        this->gen_01_delta_1125_dspsetup();
        this->gen_01_delta_1131_dspsetup();
        this->gen_01_latch_1136_dspsetup();
        this->gen_01_latch_1144_dspsetup();
        this->gen_01_latch_1174_dspsetup();
        this->gen_01_latch_1188_dspsetup();
        this->gen_01_phasor_1219_dspsetup();
        this->gen_01_delta_1221_dspsetup();
        this->gen_01_delta_1227_dspsetup();
        this->gen_01_latch_1231_dspsetup();
        this->gen_01_latch_1239_dspsetup();
        this->gen_01_latch_1269_dspsetup();
        this->gen_01_latch_1284_dspsetup();
        this->gen_01_phasor_1315_dspsetup();
        this->gen_01_delta_1317_dspsetup();
        this->gen_01_delta_1323_dspsetup();
        this->gen_01_latch_1327_dspsetup();
        this->gen_01_latch_1335_dspsetup();
        this->gen_01_latch_1365_dspsetup();
        this->gen_01_latch_1380_dspsetup();
        this->gen_01_phasor_1412_dspsetup();
        this->gen_01_delta_1414_dspsetup();
        this->gen_01_delta_1420_dspsetup();
        this->gen_01_latch_1424_dspsetup();
        this->gen_01_latch_1432_dspsetup();
        this->gen_01_latch_1462_dspsetup();
        this->gen_01_latch_1476_dspsetup();
        this->gen_01_phasor_1507_dspsetup();
        this->gen_01_delta_1509_dspsetup();
        this->gen_01_delta_1515_dspsetup();
        this->gen_01_latch_1519_dspsetup();
        this->gen_01_latch_1527_dspsetup();
        this->gen_01_latch_1557_dspsetup();
        this->gen_01_latch_1571_dspsetup();
        this->gen_01_phasor_1599_dspsetup();
        this->gen_01_delta_1601_dspsetup();
        this->gen_01_delta_1607_dspsetup();
        this->gen_01_latch_1611_dspsetup();
        this->gen_01_latch_1619_dspsetup();
        this->gen_01_latch_1652_dspsetup();
        this->gen_01_latch_1667_dspsetup();
        this->gen_01_phasor_1695_dspsetup();
        this->gen_01_delta_1697_dspsetup();
        this->gen_01_delta_1703_dspsetup();
        this->gen_01_latch_1707_dspsetup();
        this->gen_01_latch_1710_dspsetup();
        this->gen_01_latch_1749_dspsetup();
        this->gen_01_latch_1763_dspsetup();
        this->gen_01_phasor_1794_dspsetup();
        this->gen_01_delta_1796_dspsetup();
        this->gen_01_delta_1802_dspsetup();
        this->gen_01_latch_1806_dspsetup();
        this->gen_01_latch_1808_dspsetup();
        this->gen_01_latch_1844_dspsetup();
        this->gen_01_latch_1858_dspsetup();
        this->gen_01_phasor_1889_dspsetup();
        this->gen_01_delta_1891_dspsetup();
        this->gen_01_delta_1897_dspsetup();
        this->gen_01_latch_1901_dspsetup();
        this->gen_01_latch_1903_dspsetup();
        this->gen_01_latch_1939_dspsetup();
        this->gen_01_latch_1954_dspsetup();
        this->gen_01_phasor_1984_dspsetup();
        this->gen_01_delta_1986_dspsetup();
        this->gen_01_delta_1992_dspsetup();
        this->gen_01_latch_1996_dspsetup();
        this->gen_01_latch_1998_dspsetup();
        this->gen_01_latch_2038_dspsetup();
        this->gen_01_latch_2052_dspsetup();
        this->gen_01_phasor_2080_dspsetup();
        this->gen_01_delta_2082_dspsetup();
        this->gen_01_delta_2089_dspsetup();
        this->gen_01_latch_2093_dspsetup();
        this->gen_01_latch_2095_dspsetup();
        this->gen_01_latch_2134_dspsetup();
        this->gen_01_latch_2149_dspsetup();
        this->gen_01_phasor_2180_dspsetup();
        this->gen_01_delta_2182_dspsetup();
        this->gen_01_delta_2188_dspsetup();
        this->gen_01_latch_2192_dspsetup();
        this->gen_01_latch_2194_dspsetup();
        this->gen_01_latch_2230_dspsetup();
        this->gen_01_latch_2244_dspsetup();
        this->gen_01_phasor_2275_dspsetup();
        this->gen_01_delta_2277_dspsetup();
        this->gen_01_delta_2283_dspsetup();
        this->gen_01_latch_2287_dspsetup();
        this->gen_01_latch_2289_dspsetup();
        this->gen_01_latch_2325_dspsetup();
        this->gen_01_latch_2339_dspsetup();
        this->gen_01_phasor_2370_dspsetup();
        this->gen_01_delta_2372_dspsetup();
        this->gen_01_delta_2378_dspsetup();
        this->gen_01_latch_2382_dspsetup();
        this->gen_01_latch_2384_dspsetup();
        this->gen_01_latch_2420_dspsetup();
        this->gen_01_latch_2434_dspsetup();
        this->gen_01_phasor_2465_dspsetup();
        this->gen_01_delta_2467_dspsetup();
        this->gen_01_delta_2473_dspsetup();
        this->gen_01_latch_2477_dspsetup();
        this->gen_01_latch_2486_dspsetup();
        this->gen_01_latch_2516_dspsetup();
        this->gen_01_latch_2531_dspsetup();
        this->gen_01_phasor_2562_dspsetup();
        this->gen_01_delta_2564_dspsetup();
        this->gen_01_delta_2570_dspsetup();
        this->gen_01_latch_2574_dspsetup();
        this->gen_01_latch_2582_dspsetup();
        this->gen_01_latch_2612_dspsetup();
        this->gen_01_latch_2626_dspsetup();
        this->gen_01_phasor_2654_dspsetup();
        this->gen_01_delta_2656_dspsetup();
        this->gen_01_delta_2663_dspsetup();
        this->gen_01_latch_2667_dspsetup();
        this->gen_01_latch_2669_dspsetup();
        this->gen_01_latch_2708_dspsetup();
        this->gen_01_latch_2722_dspsetup();
        this->gen_01_phasor_2753_dspsetup();
        this->gen_01_delta_2755_dspsetup();
        this->gen_01_delta_2761_dspsetup();
        this->gen_01_latch_2765_dspsetup();
        this->gen_01_latch_2773_dspsetup();
        this->gen_01_latch_2803_dspsetup();
        this->gen_01_latch_2817_dspsetup();
        this->gen_01_phasor_2848_dspsetup();
        this->gen_01_delta_2850_dspsetup();
        this->gen_01_delta_2856_dspsetup();
        this->gen_01_latch_2860_dspsetup();
        this->gen_01_latch_2868_dspsetup();
        this->gen_01_latch_2898_dspsetup();
        this->gen_01_latch_2912_dspsetup();
        this->gen_01_phasor_2940_dspsetup();
        this->gen_01_delta_2942_dspsetup();
        this->gen_01_delta_2948_dspsetup();
        this->gen_01_latch_2952_dspsetup();
        this->gen_01_latch_2954_dspsetup();
        this->gen_01_latch_2993_dspsetup();
        this->gen_01_latch_3007_dspsetup();
        this->gen_01_phasor_3038_dspsetup();
        this->gen_01_delta_3040_dspsetup();
        this->gen_01_delta_3046_dspsetup();
        this->gen_01_latch_3050_dspsetup();
        this->gen_01_latch_3058_dspsetup();
        this->gen_01_latch_3088_dspsetup();
        this->gen_01_latch_3102_dspsetup();
    }
    
    void data_01_init() {
        this->data_01_buffer->setWantsFill(true);
    }
    
    Index data_01_evaluateSizeExpr(number samplerate, number vectorsize) {
        RNBO_UNUSED(vectorsize);
        RNBO_UNUSED(samplerate);
        number size = 0;
        return (Index)(size);
    }
    
    void data_01_dspsetup(bool force) {
        if ((bool)(this->data_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        if (this->data_01_sizemode == 2) {
            this->data_01_buffer = this->data_01_buffer->setSize((Index)(this->mstosamps(this->data_01_sizems)));
            updateDataRef(this, this->data_01_buffer);
        } else if (this->data_01_sizemode == 3) {
            this->data_01_buffer = this->data_01_buffer->setSize(this->data_01_evaluateSizeExpr(this->sr, this->vs));
            updateDataRef(this, this->data_01_buffer);
        }
    
        this->data_01_setupDone = true;
    }
    
    void data_01_bufferUpdated() {
        this->data_01_report();
    }
    
    void data_01_report() {
        this->data_01_srout_set(this->data_01_buffer->getSampleRate());
        this->data_01_chanout_set(this->data_01_buffer->getChannels());
        this->data_01_sizeout_set(this->data_01_buffer->getSize());
    }
    
    void adsr_01_dspsetup(bool force) {
        if ((bool)(this->adsr_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->adsr_01_mspersamp = (number)1000 / this->sr;
        this->adsr_01_setupDone = true;
    }
    
    list midiparse_01_parser_next(number midiin) {
        Int midivalue = (Int)(trunc(midiin));
        list result = list(-1);
        number resetByte1 = false;
    
        if (midivalue > 127) {
            this->midiparse_01_parser_status = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0xFF);
            this->midiparse_01_parser_byte1 = -1;
        } else {
            switch ((int)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0xF0)) {
            case 0xB0:
                {
                if (this->midiparse_01_parser_byte1 == -1) {
                    this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                } else {
                    result = {
                        2,
                        this->midiparse_01_parser_byte1,
                        (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                        1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                    };
    
                    resetByte1 = true;
                }
    
                break;
                }
            case 0xA0:
                {
                if (this->midiparse_01_parser_byte1 == -1) {
                    this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                } else {
                    result = {
                        1,
                        this->midiparse_01_parser_byte1,
                        (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                        1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                    };
    
                    resetByte1 = true;
                }
    
                break;
                }
            case 0xE0:
                {
                if (this->midiparse_01_parser_byte1 == -1) {
                    this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                } else {
                    number pitchbend;
    
                    {
                        number val = this->midiparse_01_parser_byte1 + ((BinOpInt)(((BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32)));
    
                        {
                            val -= 0x2000;
                            pitchbend = val / (number)8192;
                        }
                    }
    
                    result = {
                        5,
                        pitchbend,
                        1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                    };
    
                    resetByte1 = true;
                }
    
                break;
                }
            case 0xD0:
                {
                result = {
                    4,
                    (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                    1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                };
    
                break;
                }
            case 0x90:
                {
                if (this->midiparse_01_parser_byte1 == -1) {
                    this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                } else {
                    result = {
                        0,
                        this->midiparse_01_parser_byte1,
                        (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                        1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                    };
    
                    resetByte1 = true;
                }
    
                break;
                }
            case 0xC0:
                {
                result = {
                    3,
                    (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F),
                    1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                };
    
                break;
                }
            case 0x80:
                {
                if (this->midiparse_01_parser_byte1 == -1) {
                    this->midiparse_01_parser_byte1 = (BinOpInt)((BinOpInt)midivalue & (BinOpInt)0x7F);
                } else {
                    result = {
                        0,
                        this->midiparse_01_parser_byte1,
                        0,
                        1 + ((BinOpInt)((BinOpInt)this->midiparse_01_parser_status & (BinOpInt)0x0F))
                    };
    
                    resetByte1 = true;
                }
    
                break;
                }
            default:
                {
                result = {-1};
                }
            }
        }
    
        if (result->length > 1) {
            result->push(this->midiparse_01_parser_status);
            result->push(this->midiparse_01_parser_byte1);
            result->push(midivalue);
        }
    
        if ((bool)(resetByte1)) {
            this->midiparse_01_parser_byte1 = -1;
        }
    
        return result;
    }
    
    void midiparse_01_parser_reset() {
        this->midiparse_01_parser_status = -1;
        this->midiparse_01_parser_byte1 = -1;
    }
    
    void message_01_init() {
        this->message_01_set_set(listbase<number, 1>{27});
    }
    
    void message_02_init() {
        this->message_02_set_set(listbase<number, 1>{-22});
    }
    
    void midiouthelper_sendMidi(number v) {
        this->midiouthelper_midiout_set(v);
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        if (this->_voiceIndex == 1)
            this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
        RNBO_UNUSED(inProcess);
        RNBO_UNUSED(engine);
        this->_currentTime = time;
        auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
    
        if (offset >= (SampleIndex)(this->vs))
            offset = (SampleIndex)(this->vs) - 1;
    
        if (offset < 0)
            offset = 0;
    
        this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
    }
    
    void assign_defaults()
    {
        gen_01_in1 = 0;
        gen_01_stereo = 0;
        gen_01_spray = 0;
        gen_01_position = 0;
        gen_01_density = 0;
        gen_01_pitch = 0;
        gen_01_spread = 0;
        gen_01_grain_size = 0;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        data_01_sizeout = 0;
        data_01_size = 0;
        data_01_sizems = 0;
        data_01_normalize = 0.995;
        data_01_channels = 1;
        expr_01_in1 = 0;
        expr_01_in2 = 127;
        expr_01_out1 = 0;
        adsr_01_trigger_number = 0;
        adsr_01_attack = 40;
        adsr_01_decay = 200;
        adsr_01_sustain = 1;
        adsr_01_release = 200;
        adsr_01_legato = false;
        adsr_01_maxsustain = -1;
        midiin_01_port = 0;
        expr_02_in1 = 0;
        expr_02_in2 = 0;
        expr_02_out1 = 0;
        expr_03_in1 = 0;
        expr_03_in2 = 60;
        expr_03_out1 = 0;
        unpack_01_out1 = 0;
        unpack_01_out2 = 0;
        intnum_01_input_number = 0;
        intnum_01_value = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.000022675736961451248;
        gen_01_slide_250_prev = 0;
        gen_01_slide_262_prev = 0;
        gen_01_phasor_264_currentPhase = 0;
        gen_01_phasor_264_conv = 0;
        gen_01_delta_266_prev = 0;
        gen_01_counter_269_carry = 0;
        gen_01_counter_269_count = 0;
        gen_01_delta_272_prev = 0;
        gen_01_latch_276_value = 0;
        gen_01_latch_278_value = 0;
        gen_01_counter_286_carry = 0;
        gen_01_counter_286_count = 0;
        gen_01_slide_301_prev = 0;
        gen_01_slide_311_prev = 0;
        gen_01_latch_314_value = 0;
        gen_01_slide_317_prev = 0;
        gen_01_slide_322_prev = 0;
        gen_01_latch_328_value = 0;
        gen_01_slide_346_prev = 0;
        gen_01_slide_354_prev = 0;
        gen_01_phasor_356_currentPhase = 0;
        gen_01_phasor_356_conv = 0;
        gen_01_delta_358_prev = 0;
        gen_01_counter_361_carry = 0;
        gen_01_counter_361_count = 0;
        gen_01_delta_364_prev = 0;
        gen_01_latch_368_value = 0;
        gen_01_latch_370_value = 0;
        gen_01_counter_378_carry = 0;
        gen_01_counter_378_count = 0;
        gen_01_slide_396_prev = 0;
        gen_01_slide_406_prev = 0;
        gen_01_latch_409_value = 0;
        gen_01_slide_412_prev = 0;
        gen_01_slide_417_prev = 0;
        gen_01_latch_423_value = 0;
        gen_01_slide_441_prev = 0;
        gen_01_slide_452_prev = 0;
        gen_01_phasor_454_currentPhase = 0;
        gen_01_phasor_454_conv = 0;
        gen_01_delta_456_prev = 0;
        gen_01_counter_459_carry = 0;
        gen_01_counter_459_count = 0;
        gen_01_delta_462_prev = 0;
        gen_01_latch_466_value = 0;
        gen_01_latch_469_value = 0;
        gen_01_counter_477_carry = 0;
        gen_01_counter_477_count = 0;
        gen_01_slide_492_prev = 0;
        gen_01_slide_502_prev = 0;
        gen_01_latch_505_value = 0;
        gen_01_slide_508_prev = 0;
        gen_01_slide_513_prev = 0;
        gen_01_latch_519_value = 0;
        gen_01_slide_537_prev = 0;
        gen_01_slide_549_prev = 0;
        gen_01_phasor_551_currentPhase = 0;
        gen_01_phasor_551_conv = 0;
        gen_01_delta_553_prev = 0;
        gen_01_counter_556_carry = 0;
        gen_01_counter_556_count = 0;
        gen_01_delta_559_prev = 0;
        gen_01_latch_563_value = 0;
        gen_01_latch_571_value = 0;
        gen_01_counter_573_carry = 0;
        gen_01_counter_573_count = 0;
        gen_01_slide_588_prev = 0;
        gen_01_slide_598_prev = 0;
        gen_01_latch_601_value = 0;
        gen_01_slide_604_prev = 0;
        gen_01_slide_609_prev = 0;
        gen_01_latch_615_value = 0;
        gen_01_slide_633_prev = 0;
        gen_01_slide_641_prev = 0;
        gen_01_phasor_643_currentPhase = 0;
        gen_01_phasor_643_conv = 0;
        gen_01_delta_645_prev = 0;
        gen_01_counter_648_carry = 0;
        gen_01_counter_648_count = 0;
        gen_01_delta_651_prev = 0;
        gen_01_latch_655_value = 0;
        gen_01_latch_657_value = 0;
        gen_01_counter_665_carry = 0;
        gen_01_counter_665_count = 0;
        gen_01_slide_683_prev = 0;
        gen_01_slide_693_prev = 0;
        gen_01_latch_696_value = 0;
        gen_01_slide_699_prev = 0;
        gen_01_slide_704_prev = 0;
        gen_01_latch_710_value = 0;
        gen_01_slide_728_prev = 0;
        gen_01_slide_739_prev = 0;
        gen_01_phasor_741_currentPhase = 0;
        gen_01_phasor_741_conv = 0;
        gen_01_delta_743_prev = 0;
        gen_01_counter_746_carry = 0;
        gen_01_counter_746_count = 0;
        gen_01_delta_749_prev = 0;
        gen_01_latch_753_value = 0;
        gen_01_latch_755_value = 0;
        gen_01_counter_763_carry = 0;
        gen_01_counter_763_count = 0;
        gen_01_slide_778_prev = 0;
        gen_01_slide_788_prev = 0;
        gen_01_latch_791_value = 0;
        gen_01_slide_795_prev = 0;
        gen_01_slide_800_prev = 0;
        gen_01_latch_806_value = 0;
        gen_01_slide_824_prev = 0;
        gen_01_slide_836_prev = 0;
        gen_01_phasor_838_currentPhase = 0;
        gen_01_phasor_838_conv = 0;
        gen_01_delta_840_prev = 0;
        gen_01_counter_843_carry = 0;
        gen_01_counter_843_count = 0;
        gen_01_delta_846_prev = 0;
        gen_01_latch_850_value = 0;
        gen_01_latch_852_value = 0;
        gen_01_counter_860_carry = 0;
        gen_01_counter_860_count = 0;
        gen_01_slide_875_prev = 0;
        gen_01_slide_885_prev = 0;
        gen_01_latch_888_value = 0;
        gen_01_slide_891_prev = 0;
        gen_01_slide_896_prev = 0;
        gen_01_latch_902_value = 0;
        gen_01_slide_920_prev = 0;
        gen_01_slide_931_prev = 0;
        gen_01_phasor_933_currentPhase = 0;
        gen_01_phasor_933_conv = 0;
        gen_01_delta_935_prev = 0;
        gen_01_counter_938_carry = 0;
        gen_01_counter_938_count = 0;
        gen_01_delta_941_prev = 0;
        gen_01_latch_945_value = 0;
        gen_01_latch_947_value = 0;
        gen_01_counter_955_carry = 0;
        gen_01_counter_955_count = 0;
        gen_01_slide_970_prev = 0;
        gen_01_slide_980_prev = 0;
        gen_01_latch_983_value = 0;
        gen_01_slide_986_prev = 0;
        gen_01_slide_991_prev = 0;
        gen_01_latch_997_value = 0;
        gen_01_slide_1015_prev = 0;
        gen_01_slide_1023_prev = 0;
        gen_01_phasor_1025_currentPhase = 0;
        gen_01_phasor_1025_conv = 0;
        gen_01_delta_1027_prev = 0;
        gen_01_counter_1030_carry = 0;
        gen_01_counter_1030_count = 0;
        gen_01_delta_1033_prev = 0;
        gen_01_latch_1037_value = 0;
        gen_01_latch_1039_value = 0;
        gen_01_counter_1047_carry = 0;
        gen_01_counter_1047_count = 0;
        gen_01_slide_1065_prev = 0;
        gen_01_slide_1075_prev = 0;
        gen_01_latch_1078_value = 0;
        gen_01_slide_1081_prev = 0;
        gen_01_slide_1086_prev = 0;
        gen_01_latch_1092_value = 0;
        gen_01_slide_1110_prev = 0;
        gen_01_slide_1121_prev = 0;
        gen_01_phasor_1123_currentPhase = 0;
        gen_01_phasor_1123_conv = 0;
        gen_01_delta_1125_prev = 0;
        gen_01_counter_1128_carry = 0;
        gen_01_counter_1128_count = 0;
        gen_01_delta_1131_prev = 0;
        gen_01_latch_1136_value = 0;
        gen_01_latch_1144_value = 0;
        gen_01_counter_1146_carry = 0;
        gen_01_counter_1146_count = 0;
        gen_01_slide_1161_prev = 0;
        gen_01_slide_1171_prev = 0;
        gen_01_latch_1174_value = 0;
        gen_01_slide_1177_prev = 0;
        gen_01_slide_1182_prev = 0;
        gen_01_latch_1188_value = 0;
        gen_01_slide_1206_prev = 0;
        gen_01_slide_1217_prev = 0;
        gen_01_phasor_1219_currentPhase = 0;
        gen_01_phasor_1219_conv = 0;
        gen_01_delta_1221_prev = 0;
        gen_01_counter_1224_carry = 0;
        gen_01_counter_1224_count = 0;
        gen_01_delta_1227_prev = 0;
        gen_01_latch_1231_value = 0;
        gen_01_latch_1239_value = 0;
        gen_01_counter_1241_carry = 0;
        gen_01_counter_1241_count = 0;
        gen_01_slide_1256_prev = 0;
        gen_01_slide_1266_prev = 0;
        gen_01_latch_1269_value = 0;
        gen_01_slide_1272_prev = 0;
        gen_01_slide_1278_prev = 0;
        gen_01_latch_1284_value = 0;
        gen_01_slide_1302_prev = 0;
        gen_01_slide_1313_prev = 0;
        gen_01_phasor_1315_currentPhase = 0;
        gen_01_phasor_1315_conv = 0;
        gen_01_delta_1317_prev = 0;
        gen_01_counter_1320_carry = 0;
        gen_01_counter_1320_count = 0;
        gen_01_delta_1323_prev = 0;
        gen_01_latch_1327_value = 0;
        gen_01_latch_1335_value = 0;
        gen_01_counter_1337_carry = 0;
        gen_01_counter_1337_count = 0;
        gen_01_slide_1352_prev = 0;
        gen_01_slide_1362_prev = 0;
        gen_01_latch_1365_value = 0;
        gen_01_slide_1369_prev = 0;
        gen_01_slide_1374_prev = 0;
        gen_01_latch_1380_value = 0;
        gen_01_slide_1398_prev = 0;
        gen_01_slide_1410_prev = 0;
        gen_01_phasor_1412_currentPhase = 0;
        gen_01_phasor_1412_conv = 0;
        gen_01_delta_1414_prev = 0;
        gen_01_counter_1417_carry = 0;
        gen_01_counter_1417_count = 0;
        gen_01_delta_1420_prev = 0;
        gen_01_latch_1424_value = 0;
        gen_01_latch_1432_value = 0;
        gen_01_counter_1434_carry = 0;
        gen_01_counter_1434_count = 0;
        gen_01_slide_1449_prev = 0;
        gen_01_slide_1459_prev = 0;
        gen_01_latch_1462_value = 0;
        gen_01_slide_1465_prev = 0;
        gen_01_slide_1470_prev = 0;
        gen_01_latch_1476_value = 0;
        gen_01_slide_1494_prev = 0;
        gen_01_slide_1505_prev = 0;
        gen_01_phasor_1507_currentPhase = 0;
        gen_01_phasor_1507_conv = 0;
        gen_01_delta_1509_prev = 0;
        gen_01_counter_1512_carry = 0;
        gen_01_counter_1512_count = 0;
        gen_01_delta_1515_prev = 0;
        gen_01_latch_1519_value = 0;
        gen_01_latch_1527_value = 0;
        gen_01_counter_1529_carry = 0;
        gen_01_counter_1529_count = 0;
        gen_01_slide_1544_prev = 0;
        gen_01_slide_1554_prev = 0;
        gen_01_latch_1557_value = 0;
        gen_01_slide_1560_prev = 0;
        gen_01_slide_1565_prev = 0;
        gen_01_latch_1571_value = 0;
        gen_01_slide_1589_prev = 0;
        gen_01_slide_1597_prev = 0;
        gen_01_phasor_1599_currentPhase = 0;
        gen_01_phasor_1599_conv = 0;
        gen_01_delta_1601_prev = 0;
        gen_01_counter_1604_carry = 0;
        gen_01_counter_1604_count = 0;
        gen_01_delta_1607_prev = 0;
        gen_01_latch_1611_value = 0;
        gen_01_latch_1619_value = 0;
        gen_01_counter_1621_carry = 0;
        gen_01_counter_1621_count = 0;
        gen_01_slide_1639_prev = 0;
        gen_01_slide_1649_prev = 0;
        gen_01_latch_1652_value = 0;
        gen_01_slide_1655_prev = 0;
        gen_01_slide_1660_prev = 0;
        gen_01_latch_1667_value = 0;
        gen_01_slide_1685_prev = 0;
        gen_01_slide_1693_prev = 0;
        gen_01_phasor_1695_currentPhase = 0;
        gen_01_phasor_1695_conv = 0;
        gen_01_delta_1697_prev = 0;
        gen_01_counter_1700_carry = 0;
        gen_01_counter_1700_count = 0;
        gen_01_delta_1703_prev = 0;
        gen_01_latch_1707_value = 0;
        gen_01_latch_1710_value = 0;
        gen_01_counter_1718_carry = 0;
        gen_01_counter_1718_count = 0;
        gen_01_slide_1736_prev = 0;
        gen_01_slide_1746_prev = 0;
        gen_01_latch_1749_value = 0;
        gen_01_slide_1752_prev = 0;
        gen_01_slide_1757_prev = 0;
        gen_01_latch_1763_value = 0;
        gen_01_slide_1781_prev = 0;
        gen_01_slide_1792_prev = 0;
        gen_01_phasor_1794_currentPhase = 0;
        gen_01_phasor_1794_conv = 0;
        gen_01_delta_1796_prev = 0;
        gen_01_counter_1799_carry = 0;
        gen_01_counter_1799_count = 0;
        gen_01_delta_1802_prev = 0;
        gen_01_latch_1806_value = 0;
        gen_01_latch_1808_value = 0;
        gen_01_counter_1816_carry = 0;
        gen_01_counter_1816_count = 0;
        gen_01_slide_1831_prev = 0;
        gen_01_slide_1841_prev = 0;
        gen_01_latch_1844_value = 0;
        gen_01_slide_1847_prev = 0;
        gen_01_slide_1852_prev = 0;
        gen_01_latch_1858_value = 0;
        gen_01_slide_1876_prev = 0;
        gen_01_slide_1887_prev = 0;
        gen_01_phasor_1889_currentPhase = 0;
        gen_01_phasor_1889_conv = 0;
        gen_01_delta_1891_prev = 0;
        gen_01_counter_1894_carry = 0;
        gen_01_counter_1894_count = 0;
        gen_01_delta_1897_prev = 0;
        gen_01_latch_1901_value = 0;
        gen_01_latch_1903_value = 0;
        gen_01_counter_1911_carry = 0;
        gen_01_counter_1911_count = 0;
        gen_01_slide_1926_prev = 0;
        gen_01_slide_1936_prev = 0;
        gen_01_latch_1939_value = 0;
        gen_01_slide_1943_prev = 0;
        gen_01_slide_1948_prev = 0;
        gen_01_latch_1954_value = 0;
        gen_01_slide_1972_prev = 0;
        gen_01_slide_1981_prev = 0;
        gen_01_phasor_1984_currentPhase = 0;
        gen_01_phasor_1984_conv = 0;
        gen_01_delta_1986_prev = 0;
        gen_01_counter_1989_carry = 0;
        gen_01_counter_1989_count = 0;
        gen_01_delta_1992_prev = 0;
        gen_01_latch_1996_value = 0;
        gen_01_latch_1998_value = 0;
        gen_01_counter_2006_carry = 0;
        gen_01_counter_2006_count = 0;
        gen_01_slide_2025_prev = 0;
        gen_01_slide_2035_prev = 0;
        gen_01_latch_2038_value = 0;
        gen_01_slide_2041_prev = 0;
        gen_01_slide_2046_prev = 0;
        gen_01_latch_2052_value = 0;
        gen_01_slide_2070_prev = 0;
        gen_01_slide_2078_prev = 0;
        gen_01_phasor_2080_currentPhase = 0;
        gen_01_phasor_2080_conv = 0;
        gen_01_delta_2082_prev = 0;
        gen_01_counter_2086_carry = 0;
        gen_01_counter_2086_count = 0;
        gen_01_delta_2089_prev = 0;
        gen_01_latch_2093_value = 0;
        gen_01_latch_2095_value = 0;
        gen_01_counter_2103_carry = 0;
        gen_01_counter_2103_count = 0;
        gen_01_slide_2121_prev = 0;
        gen_01_slide_2131_prev = 0;
        gen_01_latch_2134_value = 0;
        gen_01_slide_2138_prev = 0;
        gen_01_slide_2143_prev = 0;
        gen_01_latch_2149_value = 0;
        gen_01_slide_2167_prev = 0;
        gen_01_slide_2178_prev = 0;
        gen_01_phasor_2180_currentPhase = 0;
        gen_01_phasor_2180_conv = 0;
        gen_01_delta_2182_prev = 0;
        gen_01_counter_2185_carry = 0;
        gen_01_counter_2185_count = 0;
        gen_01_delta_2188_prev = 0;
        gen_01_latch_2192_value = 0;
        gen_01_latch_2194_value = 0;
        gen_01_counter_2202_carry = 0;
        gen_01_counter_2202_count = 0;
        gen_01_slide_2217_prev = 0;
        gen_01_slide_2227_prev = 0;
        gen_01_latch_2230_value = 0;
        gen_01_slide_2233_prev = 0;
        gen_01_slide_2238_prev = 0;
        gen_01_latch_2244_value = 0;
        gen_01_slide_2262_prev = 0;
        gen_01_slide_2273_prev = 0;
        gen_01_phasor_2275_currentPhase = 0;
        gen_01_phasor_2275_conv = 0;
        gen_01_delta_2277_prev = 0;
        gen_01_counter_2280_carry = 0;
        gen_01_counter_2280_count = 0;
        gen_01_delta_2283_prev = 0;
        gen_01_latch_2287_value = 0;
        gen_01_latch_2289_value = 0;
        gen_01_counter_2297_carry = 0;
        gen_01_counter_2297_count = 0;
        gen_01_slide_2312_prev = 0;
        gen_01_slide_2322_prev = 0;
        gen_01_latch_2325_value = 0;
        gen_01_slide_2328_prev = 0;
        gen_01_slide_2333_prev = 0;
        gen_01_latch_2339_value = 0;
        gen_01_slide_2357_prev = 0;
        gen_01_slide_2368_prev = 0;
        gen_01_phasor_2370_currentPhase = 0;
        gen_01_phasor_2370_conv = 0;
        gen_01_delta_2372_prev = 0;
        gen_01_counter_2375_carry = 0;
        gen_01_counter_2375_count = 0;
        gen_01_delta_2378_prev = 0;
        gen_01_latch_2382_value = 0;
        gen_01_latch_2384_value = 0;
        gen_01_counter_2392_carry = 0;
        gen_01_counter_2392_count = 0;
        gen_01_slide_2407_prev = 0;
        gen_01_slide_2417_prev = 0;
        gen_01_latch_2420_value = 0;
        gen_01_slide_2423_prev = 0;
        gen_01_slide_2428_prev = 0;
        gen_01_latch_2434_value = 0;
        gen_01_slide_2452_prev = 0;
        gen_01_slide_2463_prev = 0;
        gen_01_phasor_2465_currentPhase = 0;
        gen_01_phasor_2465_conv = 0;
        gen_01_delta_2467_prev = 0;
        gen_01_counter_2470_carry = 0;
        gen_01_counter_2470_count = 0;
        gen_01_delta_2473_prev = 0;
        gen_01_latch_2477_value = 0;
        gen_01_latch_2486_value = 0;
        gen_01_counter_2488_carry = 0;
        gen_01_counter_2488_count = 0;
        gen_01_slide_2503_prev = 0;
        gen_01_slide_2513_prev = 0;
        gen_01_latch_2516_value = 0;
        gen_01_slide_2519_prev = 0;
        gen_01_slide_2525_prev = 0;
        gen_01_latch_2531_value = 0;
        gen_01_slide_2549_prev = 0;
        gen_01_slide_2560_prev = 0;
        gen_01_phasor_2562_currentPhase = 0;
        gen_01_phasor_2562_conv = 0;
        gen_01_delta_2564_prev = 0;
        gen_01_counter_2567_carry = 0;
        gen_01_counter_2567_count = 0;
        gen_01_delta_2570_prev = 0;
        gen_01_latch_2574_value = 0;
        gen_01_latch_2582_value = 0;
        gen_01_counter_2584_carry = 0;
        gen_01_counter_2584_count = 0;
        gen_01_slide_2599_prev = 0;
        gen_01_slide_2609_prev = 0;
        gen_01_latch_2612_value = 0;
        gen_01_slide_2615_prev = 0;
        gen_01_slide_2620_prev = 0;
        gen_01_latch_2626_value = 0;
        gen_01_slide_2644_prev = 0;
        gen_01_slide_2652_prev = 0;
        gen_01_phasor_2654_currentPhase = 0;
        gen_01_phasor_2654_conv = 0;
        gen_01_delta_2656_prev = 0;
        gen_01_counter_2660_carry = 0;
        gen_01_counter_2660_count = 0;
        gen_01_delta_2663_prev = 0;
        gen_01_latch_2667_value = 0;
        gen_01_latch_2669_value = 0;
        gen_01_counter_2677_carry = 0;
        gen_01_counter_2677_count = 0;
        gen_01_slide_2695_prev = 0;
        gen_01_slide_2705_prev = 0;
        gen_01_latch_2708_value = 0;
        gen_01_slide_2711_prev = 0;
        gen_01_slide_2716_prev = 0;
        gen_01_latch_2722_value = 0;
        gen_01_slide_2740_prev = 0;
        gen_01_slide_2751_prev = 0;
        gen_01_phasor_2753_currentPhase = 0;
        gen_01_phasor_2753_conv = 0;
        gen_01_delta_2755_prev = 0;
        gen_01_counter_2758_carry = 0;
        gen_01_counter_2758_count = 0;
        gen_01_delta_2761_prev = 0;
        gen_01_latch_2765_value = 0;
        gen_01_latch_2773_value = 0;
        gen_01_counter_2775_carry = 0;
        gen_01_counter_2775_count = 0;
        gen_01_slide_2790_prev = 0;
        gen_01_slide_2800_prev = 0;
        gen_01_latch_2803_value = 0;
        gen_01_slide_2806_prev = 0;
        gen_01_slide_2811_prev = 0;
        gen_01_latch_2817_value = 0;
        gen_01_slide_2835_prev = 0;
        gen_01_slide_2846_prev = 0;
        gen_01_phasor_2848_currentPhase = 0;
        gen_01_phasor_2848_conv = 0;
        gen_01_delta_2850_prev = 0;
        gen_01_counter_2853_carry = 0;
        gen_01_counter_2853_count = 0;
        gen_01_delta_2856_prev = 0;
        gen_01_latch_2860_value = 0;
        gen_01_latch_2868_value = 0;
        gen_01_counter_2870_carry = 0;
        gen_01_counter_2870_count = 0;
        gen_01_slide_2885_prev = 0;
        gen_01_slide_2895_prev = 0;
        gen_01_latch_2898_value = 0;
        gen_01_slide_2901_prev = 0;
        gen_01_slide_2906_prev = 0;
        gen_01_latch_2912_value = 0;
        gen_01_slide_2930_prev = 0;
        gen_01_slide_2938_prev = 0;
        gen_01_phasor_2940_currentPhase = 0;
        gen_01_phasor_2940_conv = 0;
        gen_01_delta_2942_prev = 0;
        gen_01_counter_2945_carry = 0;
        gen_01_counter_2945_count = 0;
        gen_01_delta_2948_prev = 0;
        gen_01_latch_2952_value = 0;
        gen_01_latch_2954_value = 0;
        gen_01_counter_2962_carry = 0;
        gen_01_counter_2962_count = 0;
        gen_01_slide_2980_prev = 0;
        gen_01_slide_2990_prev = 0;
        gen_01_latch_2993_value = 0;
        gen_01_slide_2996_prev = 0;
        gen_01_slide_3001_prev = 0;
        gen_01_latch_3007_value = 0;
        gen_01_slide_3025_prev = 0;
        gen_01_slide_3036_prev = 0;
        gen_01_phasor_3038_currentPhase = 0;
        gen_01_phasor_3038_conv = 0;
        gen_01_delta_3040_prev = 0;
        gen_01_counter_3043_carry = 0;
        gen_01_counter_3043_count = 0;
        gen_01_delta_3046_prev = 0;
        gen_01_latch_3050_value = 0;
        gen_01_latch_3058_value = 0;
        gen_01_counter_3060_carry = 0;
        gen_01_counter_3060_count = 0;
        gen_01_slide_3075_prev = 0;
        gen_01_slide_3085_prev = 0;
        gen_01_latch_3088_value = 0;
        gen_01_slide_3091_prev = 0;
        gen_01_slide_3096_prev = 0;
        gen_01_latch_3102_value = 0;
        gen_01_setupDone = false;
        data_01_sizemode = 0;
        data_01_setupDone = false;
        adsr_01_phase = 1;
        adsr_01_mspersamp = 0;
        adsr_01_time = 0;
        adsr_01_lastTriggerVal = 0;
        adsr_01_amplitude = 0;
        adsr_01_outval = 0;
        adsr_01_startingpoint = 0;
        adsr_01_triggerBuf = nullptr;
        adsr_01_triggerValueBuf = nullptr;
        adsr_01_setupDone = false;
        midiparse_01_parser_status = -1;
        midiparse_01_parser_byte1 = -1;
        intnum_01_stored = 0;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
    // member variables
    
        number gen_01_in1;
        number gen_01_stereo;
        number gen_01_spray;
        number gen_01_position;
        number gen_01_density;
        number gen_01_pitch;
        number gen_01_spread;
        number gen_01_grain_size;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number data_01_sizeout;
        number data_01_size;
        number data_01_sizems;
        number data_01_normalize;
        number data_01_channels;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_out1;
        number adsr_01_trigger_number;
        number adsr_01_attack;
        number adsr_01_decay;
        number adsr_01_sustain;
        number adsr_01_release;
        number adsr_01_legato;
        number adsr_01_maxsustain;
        number midiin_01_port;
        number expr_02_in1;
        number expr_02_in2;
        number expr_02_out1;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number unpack_01_out1;
        number unpack_01_out2;
        number intnum_01_input_number;
        number intnum_01_value;
        list message_01_set;
        list message_02_set;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        Index sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[4];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        Float32BufferRef gen_01_sample;
        number gen_01_slide_250_prev;
        UInt gen_01_noise_253_state[4] = { };
        number gen_01_slide_262_prev;
        number gen_01_phasor_264_currentPhase;
        number gen_01_phasor_264_conv;
        number gen_01_delta_266_prev;
        Int gen_01_counter_269_carry;
        number gen_01_counter_269_count;
        number gen_01_delta_272_prev;
        number gen_01_latch_276_value;
        number gen_01_latch_278_value;
        Int gen_01_counter_286_carry;
        number gen_01_counter_286_count;
        UInt gen_01_noise_295_state[4] = { };
        UInt gen_01_noise_297_state[4] = { };
        number gen_01_slide_301_prev;
        number gen_01_slide_311_prev;
        number gen_01_latch_314_value;
        number gen_01_slide_317_prev;
        number gen_01_slide_322_prev;
        number gen_01_latch_328_value;
        number gen_01_slide_346_prev;
        UInt gen_01_noise_348_state[4] = { };
        number gen_01_slide_354_prev;
        number gen_01_phasor_356_currentPhase;
        number gen_01_phasor_356_conv;
        number gen_01_delta_358_prev;
        Int gen_01_counter_361_carry;
        number gen_01_counter_361_count;
        number gen_01_delta_364_prev;
        number gen_01_latch_368_value;
        number gen_01_latch_370_value;
        Int gen_01_counter_378_carry;
        number gen_01_counter_378_count;
        UInt gen_01_noise_390_state[4] = { };
        UInt gen_01_noise_392_state[4] = { };
        number gen_01_slide_396_prev;
        number gen_01_slide_406_prev;
        number gen_01_latch_409_value;
        number gen_01_slide_412_prev;
        number gen_01_slide_417_prev;
        number gen_01_latch_423_value;
        number gen_01_slide_441_prev;
        UInt gen_01_noise_443_state[4] = { };
        number gen_01_slide_452_prev;
        number gen_01_phasor_454_currentPhase;
        number gen_01_phasor_454_conv;
        number gen_01_delta_456_prev;
        Int gen_01_counter_459_carry;
        number gen_01_counter_459_count;
        number gen_01_delta_462_prev;
        number gen_01_latch_466_value;
        number gen_01_latch_469_value;
        Int gen_01_counter_477_carry;
        number gen_01_counter_477_count;
        UInt gen_01_noise_486_state[4] = { };
        UInt gen_01_noise_488_state[4] = { };
        number gen_01_slide_492_prev;
        number gen_01_slide_502_prev;
        number gen_01_latch_505_value;
        number gen_01_slide_508_prev;
        number gen_01_slide_513_prev;
        number gen_01_latch_519_value;
        number gen_01_slide_537_prev;
        UInt gen_01_noise_539_state[4] = { };
        number gen_01_slide_549_prev;
        number gen_01_phasor_551_currentPhase;
        number gen_01_phasor_551_conv;
        number gen_01_delta_553_prev;
        Int gen_01_counter_556_carry;
        number gen_01_counter_556_count;
        number gen_01_delta_559_prev;
        number gen_01_latch_563_value;
        number gen_01_latch_571_value;
        Int gen_01_counter_573_carry;
        number gen_01_counter_573_count;
        UInt gen_01_noise_582_state[4] = { };
        UInt gen_01_noise_584_state[4] = { };
        number gen_01_slide_588_prev;
        number gen_01_slide_598_prev;
        number gen_01_latch_601_value;
        number gen_01_slide_604_prev;
        number gen_01_slide_609_prev;
        number gen_01_latch_615_value;
        number gen_01_slide_633_prev;
        UInt gen_01_noise_635_state[4] = { };
        number gen_01_slide_641_prev;
        number gen_01_phasor_643_currentPhase;
        number gen_01_phasor_643_conv;
        number gen_01_delta_645_prev;
        Int gen_01_counter_648_carry;
        number gen_01_counter_648_count;
        number gen_01_delta_651_prev;
        number gen_01_latch_655_value;
        number gen_01_latch_657_value;
        Int gen_01_counter_665_carry;
        number gen_01_counter_665_count;
        UInt gen_01_noise_677_state[4] = { };
        UInt gen_01_noise_679_state[4] = { };
        number gen_01_slide_683_prev;
        number gen_01_slide_693_prev;
        number gen_01_latch_696_value;
        number gen_01_slide_699_prev;
        number gen_01_slide_704_prev;
        number gen_01_latch_710_value;
        number gen_01_slide_728_prev;
        UInt gen_01_noise_730_state[4] = { };
        number gen_01_slide_739_prev;
        number gen_01_phasor_741_currentPhase;
        number gen_01_phasor_741_conv;
        number gen_01_delta_743_prev;
        Int gen_01_counter_746_carry;
        number gen_01_counter_746_count;
        number gen_01_delta_749_prev;
        number gen_01_latch_753_value;
        number gen_01_latch_755_value;
        Int gen_01_counter_763_carry;
        number gen_01_counter_763_count;
        UInt gen_01_noise_772_state[4] = { };
        UInt gen_01_noise_774_state[4] = { };
        number gen_01_slide_778_prev;
        number gen_01_slide_788_prev;
        number gen_01_latch_791_value;
        number gen_01_slide_795_prev;
        number gen_01_slide_800_prev;
        number gen_01_latch_806_value;
        number gen_01_slide_824_prev;
        UInt gen_01_noise_827_state[4] = { };
        number gen_01_slide_836_prev;
        number gen_01_phasor_838_currentPhase;
        number gen_01_phasor_838_conv;
        number gen_01_delta_840_prev;
        Int gen_01_counter_843_carry;
        number gen_01_counter_843_count;
        number gen_01_delta_846_prev;
        number gen_01_latch_850_value;
        number gen_01_latch_852_value;
        Int gen_01_counter_860_carry;
        number gen_01_counter_860_count;
        UInt gen_01_noise_869_state[4] = { };
        UInt gen_01_noise_871_state[4] = { };
        number gen_01_slide_875_prev;
        number gen_01_slide_885_prev;
        number gen_01_latch_888_value;
        number gen_01_slide_891_prev;
        number gen_01_slide_896_prev;
        number gen_01_latch_902_value;
        number gen_01_slide_920_prev;
        UInt gen_01_noise_922_state[4] = { };
        number gen_01_slide_931_prev;
        number gen_01_phasor_933_currentPhase;
        number gen_01_phasor_933_conv;
        number gen_01_delta_935_prev;
        Int gen_01_counter_938_carry;
        number gen_01_counter_938_count;
        number gen_01_delta_941_prev;
        number gen_01_latch_945_value;
        number gen_01_latch_947_value;
        Int gen_01_counter_955_carry;
        number gen_01_counter_955_count;
        UInt gen_01_noise_964_state[4] = { };
        UInt gen_01_noise_966_state[4] = { };
        number gen_01_slide_970_prev;
        number gen_01_slide_980_prev;
        number gen_01_latch_983_value;
        number gen_01_slide_986_prev;
        number gen_01_slide_991_prev;
        number gen_01_latch_997_value;
        number gen_01_slide_1015_prev;
        UInt gen_01_noise_1017_state[4] = { };
        number gen_01_slide_1023_prev;
        number gen_01_phasor_1025_currentPhase;
        number gen_01_phasor_1025_conv;
        number gen_01_delta_1027_prev;
        Int gen_01_counter_1030_carry;
        number gen_01_counter_1030_count;
        number gen_01_delta_1033_prev;
        number gen_01_latch_1037_value;
        number gen_01_latch_1039_value;
        Int gen_01_counter_1047_carry;
        number gen_01_counter_1047_count;
        UInt gen_01_noise_1059_state[4] = { };
        UInt gen_01_noise_1061_state[4] = { };
        number gen_01_slide_1065_prev;
        number gen_01_slide_1075_prev;
        number gen_01_latch_1078_value;
        number gen_01_slide_1081_prev;
        number gen_01_slide_1086_prev;
        number gen_01_latch_1092_value;
        number gen_01_slide_1110_prev;
        UInt gen_01_noise_1112_state[4] = { };
        number gen_01_slide_1121_prev;
        number gen_01_phasor_1123_currentPhase;
        number gen_01_phasor_1123_conv;
        number gen_01_delta_1125_prev;
        Int gen_01_counter_1128_carry;
        number gen_01_counter_1128_count;
        number gen_01_delta_1131_prev;
        number gen_01_latch_1136_value;
        number gen_01_latch_1144_value;
        Int gen_01_counter_1146_carry;
        number gen_01_counter_1146_count;
        UInt gen_01_noise_1155_state[4] = { };
        UInt gen_01_noise_1157_state[4] = { };
        number gen_01_slide_1161_prev;
        number gen_01_slide_1171_prev;
        number gen_01_latch_1174_value;
        number gen_01_slide_1177_prev;
        number gen_01_slide_1182_prev;
        number gen_01_latch_1188_value;
        number gen_01_slide_1206_prev;
        UInt gen_01_noise_1208_state[4] = { };
        number gen_01_slide_1217_prev;
        number gen_01_phasor_1219_currentPhase;
        number gen_01_phasor_1219_conv;
        number gen_01_delta_1221_prev;
        Int gen_01_counter_1224_carry;
        number gen_01_counter_1224_count;
        number gen_01_delta_1227_prev;
        number gen_01_latch_1231_value;
        number gen_01_latch_1239_value;
        Int gen_01_counter_1241_carry;
        number gen_01_counter_1241_count;
        UInt gen_01_noise_1250_state[4] = { };
        UInt gen_01_noise_1252_state[4] = { };
        number gen_01_slide_1256_prev;
        number gen_01_slide_1266_prev;
        number gen_01_latch_1269_value;
        number gen_01_slide_1272_prev;
        number gen_01_slide_1278_prev;
        number gen_01_latch_1284_value;
        number gen_01_slide_1302_prev;
        UInt gen_01_noise_1304_state[4] = { };
        number gen_01_slide_1313_prev;
        number gen_01_phasor_1315_currentPhase;
        number gen_01_phasor_1315_conv;
        number gen_01_delta_1317_prev;
        Int gen_01_counter_1320_carry;
        number gen_01_counter_1320_count;
        number gen_01_delta_1323_prev;
        number gen_01_latch_1327_value;
        number gen_01_latch_1335_value;
        Int gen_01_counter_1337_carry;
        number gen_01_counter_1337_count;
        UInt gen_01_noise_1346_state[4] = { };
        UInt gen_01_noise_1348_state[4] = { };
        number gen_01_slide_1352_prev;
        number gen_01_slide_1362_prev;
        number gen_01_latch_1365_value;
        number gen_01_slide_1369_prev;
        number gen_01_slide_1374_prev;
        number gen_01_latch_1380_value;
        number gen_01_slide_1398_prev;
        UInt gen_01_noise_1401_state[4] = { };
        number gen_01_slide_1410_prev;
        number gen_01_phasor_1412_currentPhase;
        number gen_01_phasor_1412_conv;
        number gen_01_delta_1414_prev;
        Int gen_01_counter_1417_carry;
        number gen_01_counter_1417_count;
        number gen_01_delta_1420_prev;
        number gen_01_latch_1424_value;
        number gen_01_latch_1432_value;
        Int gen_01_counter_1434_carry;
        number gen_01_counter_1434_count;
        UInt gen_01_noise_1443_state[4] = { };
        UInt gen_01_noise_1445_state[4] = { };
        number gen_01_slide_1449_prev;
        number gen_01_slide_1459_prev;
        number gen_01_latch_1462_value;
        number gen_01_slide_1465_prev;
        number gen_01_slide_1470_prev;
        number gen_01_latch_1476_value;
        number gen_01_slide_1494_prev;
        UInt gen_01_noise_1496_state[4] = { };
        number gen_01_slide_1505_prev;
        number gen_01_phasor_1507_currentPhase;
        number gen_01_phasor_1507_conv;
        number gen_01_delta_1509_prev;
        Int gen_01_counter_1512_carry;
        number gen_01_counter_1512_count;
        number gen_01_delta_1515_prev;
        number gen_01_latch_1519_value;
        number gen_01_latch_1527_value;
        Int gen_01_counter_1529_carry;
        number gen_01_counter_1529_count;
        UInt gen_01_noise_1538_state[4] = { };
        UInt gen_01_noise_1540_state[4] = { };
        number gen_01_slide_1544_prev;
        number gen_01_slide_1554_prev;
        number gen_01_latch_1557_value;
        number gen_01_slide_1560_prev;
        number gen_01_slide_1565_prev;
        number gen_01_latch_1571_value;
        number gen_01_slide_1589_prev;
        UInt gen_01_noise_1591_state[4] = { };
        number gen_01_slide_1597_prev;
        number gen_01_phasor_1599_currentPhase;
        number gen_01_phasor_1599_conv;
        number gen_01_delta_1601_prev;
        Int gen_01_counter_1604_carry;
        number gen_01_counter_1604_count;
        number gen_01_delta_1607_prev;
        number gen_01_latch_1611_value;
        number gen_01_latch_1619_value;
        Int gen_01_counter_1621_carry;
        number gen_01_counter_1621_count;
        UInt gen_01_noise_1633_state[4] = { };
        UInt gen_01_noise_1635_state[4] = { };
        number gen_01_slide_1639_prev;
        number gen_01_slide_1649_prev;
        number gen_01_latch_1652_value;
        number gen_01_slide_1655_prev;
        number gen_01_slide_1660_prev;
        number gen_01_latch_1667_value;
        number gen_01_slide_1685_prev;
        UInt gen_01_noise_1687_state[4] = { };
        number gen_01_slide_1693_prev;
        number gen_01_phasor_1695_currentPhase;
        number gen_01_phasor_1695_conv;
        number gen_01_delta_1697_prev;
        Int gen_01_counter_1700_carry;
        number gen_01_counter_1700_count;
        number gen_01_delta_1703_prev;
        number gen_01_latch_1707_value;
        number gen_01_latch_1710_value;
        Int gen_01_counter_1718_carry;
        number gen_01_counter_1718_count;
        UInt gen_01_noise_1730_state[4] = { };
        UInt gen_01_noise_1732_state[4] = { };
        number gen_01_slide_1736_prev;
        number gen_01_slide_1746_prev;
        number gen_01_latch_1749_value;
        number gen_01_slide_1752_prev;
        number gen_01_slide_1757_prev;
        number gen_01_latch_1763_value;
        number gen_01_slide_1781_prev;
        UInt gen_01_noise_1783_state[4] = { };
        number gen_01_slide_1792_prev;
        number gen_01_phasor_1794_currentPhase;
        number gen_01_phasor_1794_conv;
        number gen_01_delta_1796_prev;
        Int gen_01_counter_1799_carry;
        number gen_01_counter_1799_count;
        number gen_01_delta_1802_prev;
        number gen_01_latch_1806_value;
        number gen_01_latch_1808_value;
        Int gen_01_counter_1816_carry;
        number gen_01_counter_1816_count;
        UInt gen_01_noise_1825_state[4] = { };
        UInt gen_01_noise_1827_state[4] = { };
        number gen_01_slide_1831_prev;
        number gen_01_slide_1841_prev;
        number gen_01_latch_1844_value;
        number gen_01_slide_1847_prev;
        number gen_01_slide_1852_prev;
        number gen_01_latch_1858_value;
        number gen_01_slide_1876_prev;
        UInt gen_01_noise_1878_state[4] = { };
        number gen_01_slide_1887_prev;
        number gen_01_phasor_1889_currentPhase;
        number gen_01_phasor_1889_conv;
        number gen_01_delta_1891_prev;
        Int gen_01_counter_1894_carry;
        number gen_01_counter_1894_count;
        number gen_01_delta_1897_prev;
        number gen_01_latch_1901_value;
        number gen_01_latch_1903_value;
        Int gen_01_counter_1911_carry;
        number gen_01_counter_1911_count;
        UInt gen_01_noise_1920_state[4] = { };
        UInt gen_01_noise_1922_state[4] = { };
        number gen_01_slide_1926_prev;
        number gen_01_slide_1936_prev;
        number gen_01_latch_1939_value;
        number gen_01_slide_1943_prev;
        number gen_01_slide_1948_prev;
        number gen_01_latch_1954_value;
        number gen_01_slide_1972_prev;
        UInt gen_01_noise_1975_state[4] = { };
        number gen_01_slide_1981_prev;
        number gen_01_phasor_1984_currentPhase;
        number gen_01_phasor_1984_conv;
        number gen_01_delta_1986_prev;
        Int gen_01_counter_1989_carry;
        number gen_01_counter_1989_count;
        number gen_01_delta_1992_prev;
        number gen_01_latch_1996_value;
        number gen_01_latch_1998_value;
        Int gen_01_counter_2006_carry;
        number gen_01_counter_2006_count;
        UInt gen_01_noise_2018_state[4] = { };
        UInt gen_01_noise_2020_state[4] = { };
        number gen_01_slide_2025_prev;
        number gen_01_slide_2035_prev;
        number gen_01_latch_2038_value;
        number gen_01_slide_2041_prev;
        number gen_01_slide_2046_prev;
        number gen_01_latch_2052_value;
        number gen_01_slide_2070_prev;
        UInt gen_01_noise_2072_state[4] = { };
        number gen_01_slide_2078_prev;
        number gen_01_phasor_2080_currentPhase;
        number gen_01_phasor_2080_conv;
        number gen_01_delta_2082_prev;
        Int gen_01_counter_2086_carry;
        number gen_01_counter_2086_count;
        number gen_01_delta_2089_prev;
        number gen_01_latch_2093_value;
        number gen_01_latch_2095_value;
        Int gen_01_counter_2103_carry;
        number gen_01_counter_2103_count;
        UInt gen_01_noise_2115_state[4] = { };
        UInt gen_01_noise_2117_state[4] = { };
        number gen_01_slide_2121_prev;
        number gen_01_slide_2131_prev;
        number gen_01_latch_2134_value;
        number gen_01_slide_2138_prev;
        number gen_01_slide_2143_prev;
        number gen_01_latch_2149_value;
        number gen_01_slide_2167_prev;
        UInt gen_01_noise_2169_state[4] = { };
        number gen_01_slide_2178_prev;
        number gen_01_phasor_2180_currentPhase;
        number gen_01_phasor_2180_conv;
        number gen_01_delta_2182_prev;
        Int gen_01_counter_2185_carry;
        number gen_01_counter_2185_count;
        number gen_01_delta_2188_prev;
        number gen_01_latch_2192_value;
        number gen_01_latch_2194_value;
        Int gen_01_counter_2202_carry;
        number gen_01_counter_2202_count;
        UInt gen_01_noise_2211_state[4] = { };
        UInt gen_01_noise_2213_state[4] = { };
        number gen_01_slide_2217_prev;
        number gen_01_slide_2227_prev;
        number gen_01_latch_2230_value;
        number gen_01_slide_2233_prev;
        number gen_01_slide_2238_prev;
        number gen_01_latch_2244_value;
        number gen_01_slide_2262_prev;
        UInt gen_01_noise_2264_state[4] = { };
        number gen_01_slide_2273_prev;
        number gen_01_phasor_2275_currentPhase;
        number gen_01_phasor_2275_conv;
        number gen_01_delta_2277_prev;
        Int gen_01_counter_2280_carry;
        number gen_01_counter_2280_count;
        number gen_01_delta_2283_prev;
        number gen_01_latch_2287_value;
        number gen_01_latch_2289_value;
        Int gen_01_counter_2297_carry;
        number gen_01_counter_2297_count;
        UInt gen_01_noise_2306_state[4] = { };
        UInt gen_01_noise_2308_state[4] = { };
        number gen_01_slide_2312_prev;
        number gen_01_slide_2322_prev;
        number gen_01_latch_2325_value;
        number gen_01_slide_2328_prev;
        number gen_01_slide_2333_prev;
        number gen_01_latch_2339_value;
        number gen_01_slide_2357_prev;
        UInt gen_01_noise_2359_state[4] = { };
        number gen_01_slide_2368_prev;
        number gen_01_phasor_2370_currentPhase;
        number gen_01_phasor_2370_conv;
        number gen_01_delta_2372_prev;
        Int gen_01_counter_2375_carry;
        number gen_01_counter_2375_count;
        number gen_01_delta_2378_prev;
        number gen_01_latch_2382_value;
        number gen_01_latch_2384_value;
        Int gen_01_counter_2392_carry;
        number gen_01_counter_2392_count;
        UInt gen_01_noise_2401_state[4] = { };
        UInt gen_01_noise_2403_state[4] = { };
        number gen_01_slide_2407_prev;
        number gen_01_slide_2417_prev;
        number gen_01_latch_2420_value;
        number gen_01_slide_2423_prev;
        number gen_01_slide_2428_prev;
        number gen_01_latch_2434_value;
        number gen_01_slide_2452_prev;
        UInt gen_01_noise_2454_state[4] = { };
        number gen_01_slide_2463_prev;
        number gen_01_phasor_2465_currentPhase;
        number gen_01_phasor_2465_conv;
        number gen_01_delta_2467_prev;
        Int gen_01_counter_2470_carry;
        number gen_01_counter_2470_count;
        number gen_01_delta_2473_prev;
        number gen_01_latch_2477_value;
        number gen_01_latch_2486_value;
        Int gen_01_counter_2488_carry;
        number gen_01_counter_2488_count;
        UInt gen_01_noise_2497_state[4] = { };
        UInt gen_01_noise_2499_state[4] = { };
        number gen_01_slide_2503_prev;
        number gen_01_slide_2513_prev;
        number gen_01_latch_2516_value;
        number gen_01_slide_2519_prev;
        number gen_01_slide_2525_prev;
        number gen_01_latch_2531_value;
        number gen_01_slide_2549_prev;
        UInt gen_01_noise_2551_state[4] = { };
        number gen_01_slide_2560_prev;
        number gen_01_phasor_2562_currentPhase;
        number gen_01_phasor_2562_conv;
        number gen_01_delta_2564_prev;
        Int gen_01_counter_2567_carry;
        number gen_01_counter_2567_count;
        number gen_01_delta_2570_prev;
        number gen_01_latch_2574_value;
        number gen_01_latch_2582_value;
        Int gen_01_counter_2584_carry;
        number gen_01_counter_2584_count;
        UInt gen_01_noise_2593_state[4] = { };
        UInt gen_01_noise_2595_state[4] = { };
        number gen_01_slide_2599_prev;
        number gen_01_slide_2609_prev;
        number gen_01_latch_2612_value;
        number gen_01_slide_2615_prev;
        number gen_01_slide_2620_prev;
        number gen_01_latch_2626_value;
        number gen_01_slide_2644_prev;
        UInt gen_01_noise_2646_state[4] = { };
        number gen_01_slide_2652_prev;
        number gen_01_phasor_2654_currentPhase;
        number gen_01_phasor_2654_conv;
        number gen_01_delta_2656_prev;
        Int gen_01_counter_2660_carry;
        number gen_01_counter_2660_count;
        number gen_01_delta_2663_prev;
        number gen_01_latch_2667_value;
        number gen_01_latch_2669_value;
        Int gen_01_counter_2677_carry;
        number gen_01_counter_2677_count;
        UInt gen_01_noise_2689_state[4] = { };
        UInt gen_01_noise_2691_state[4] = { };
        number gen_01_slide_2695_prev;
        number gen_01_slide_2705_prev;
        number gen_01_latch_2708_value;
        number gen_01_slide_2711_prev;
        number gen_01_slide_2716_prev;
        number gen_01_latch_2722_value;
        number gen_01_slide_2740_prev;
        UInt gen_01_noise_2742_state[4] = { };
        number gen_01_slide_2751_prev;
        number gen_01_phasor_2753_currentPhase;
        number gen_01_phasor_2753_conv;
        number gen_01_delta_2755_prev;
        Int gen_01_counter_2758_carry;
        number gen_01_counter_2758_count;
        number gen_01_delta_2761_prev;
        number gen_01_latch_2765_value;
        number gen_01_latch_2773_value;
        Int gen_01_counter_2775_carry;
        number gen_01_counter_2775_count;
        UInt gen_01_noise_2784_state[4] = { };
        UInt gen_01_noise_2786_state[4] = { };
        number gen_01_slide_2790_prev;
        number gen_01_slide_2800_prev;
        number gen_01_latch_2803_value;
        number gen_01_slide_2806_prev;
        number gen_01_slide_2811_prev;
        number gen_01_latch_2817_value;
        number gen_01_slide_2835_prev;
        UInt gen_01_noise_2837_state[4] = { };
        number gen_01_slide_2846_prev;
        number gen_01_phasor_2848_currentPhase;
        number gen_01_phasor_2848_conv;
        number gen_01_delta_2850_prev;
        Int gen_01_counter_2853_carry;
        number gen_01_counter_2853_count;
        number gen_01_delta_2856_prev;
        number gen_01_latch_2860_value;
        number gen_01_latch_2868_value;
        Int gen_01_counter_2870_carry;
        number gen_01_counter_2870_count;
        UInt gen_01_noise_2879_state[4] = { };
        UInt gen_01_noise_2881_state[4] = { };
        number gen_01_slide_2885_prev;
        number gen_01_slide_2895_prev;
        number gen_01_latch_2898_value;
        number gen_01_slide_2901_prev;
        number gen_01_slide_2906_prev;
        number gen_01_latch_2912_value;
        number gen_01_slide_2930_prev;
        UInt gen_01_noise_2932_state[4] = { };
        number gen_01_slide_2938_prev;
        number gen_01_phasor_2940_currentPhase;
        number gen_01_phasor_2940_conv;
        number gen_01_delta_2942_prev;
        Int gen_01_counter_2945_carry;
        number gen_01_counter_2945_count;
        number gen_01_delta_2948_prev;
        number gen_01_latch_2952_value;
        number gen_01_latch_2954_value;
        Int gen_01_counter_2962_carry;
        number gen_01_counter_2962_count;
        UInt gen_01_noise_2974_state[4] = { };
        UInt gen_01_noise_2976_state[4] = { };
        number gen_01_slide_2980_prev;
        number gen_01_slide_2990_prev;
        number gen_01_latch_2993_value;
        number gen_01_slide_2996_prev;
        number gen_01_slide_3001_prev;
        number gen_01_latch_3007_value;
        number gen_01_slide_3025_prev;
        UInt gen_01_noise_3027_state[4] = { };
        number gen_01_slide_3036_prev;
        number gen_01_phasor_3038_currentPhase;
        number gen_01_phasor_3038_conv;
        number gen_01_delta_3040_prev;
        Int gen_01_counter_3043_carry;
        number gen_01_counter_3043_count;
        number gen_01_delta_3046_prev;
        number gen_01_latch_3050_value;
        number gen_01_latch_3058_value;
        Int gen_01_counter_3060_carry;
        number gen_01_counter_3060_count;
        UInt gen_01_noise_3069_state[4] = { };
        UInt gen_01_noise_3071_state[4] = { };
        number gen_01_slide_3075_prev;
        number gen_01_slide_3085_prev;
        number gen_01_latch_3088_value;
        number gen_01_slide_3091_prev;
        number gen_01_slide_3096_prev;
        number gen_01_latch_3102_value;
        bool gen_01_setupDone;
        Float32BufferRef data_01_buffer;
        Int data_01_sizemode;
        bool data_01_setupDone;
        Int adsr_01_phase;
        number adsr_01_mspersamp;
        number adsr_01_time;
        number adsr_01_lastTriggerVal;
        number adsr_01_amplitude;
        number adsr_01_outval;
        number adsr_01_startingpoint;
        signal adsr_01_triggerBuf;
        signal adsr_01_triggerValueBuf;
        bool adsr_01_setupDone;
        Int midiparse_01_parser_status;
        Int midiparse_01_parser_byte1;
        number intnum_01_stored;
        number stackprotect_count;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        bool _isInitialized = false;
};

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
    getEngine()->flushClockEvents(this, -871642103, false);
    getEngine()->flushClockEvents(this, 2098551528, false);
    getEngine()->flushClockEvents(this, -1494586265, false);
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

number wrap(number x, number low, number high) {
    number lo;
    number hi;

    if (low == high)
        return low;

    if (low > high) {
        hi = low;
        lo = high;
    } else {
        lo = low;
        hi = high;
    }

    number range = hi - lo;

    if (x >= lo && x < hi)
        return x;

    if (range <= 0.000000001)
        return lo;

    Int numWraps = (Int)(trunc((x - lo) / range));
    numWraps = numWraps - ((x < lo ? 1 : 0));
    number result = x - range * numWraps;

    if (result >= hi)
        return result - range;
    else
        return result;
}

inline number linearinterp(number frac, number x, number y) {
    return x + (y - x) * frac;
}

inline number cubicinterp(number a, number w, number x, number y, number z) {
    number a1 = 1. + a;
    number aa = a * a1;
    number b = 1. - a;
    number b1 = 2. - a;
    number bb = b * b1;
    number fw = -.1666667 * bb * a;
    number fx = .5 * bb * a1;
    number fy = .5 * aa * b1;
    number fz = -.1666667 * aa * b;
    return w * fw + x * fx + y * fy + z * fz;
}

inline number fastcubicinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = z - y - w + x;
    number f1 = w - x - f0;
    number f2 = y - w;
    number f3 = x;
    return f0 * a * a2 + f1 * a2 + f2 * a + f3;
}

inline number splineinterp(number a, number w, number x, number y, number z) {
    number a2 = a * a;
    number f0 = -0.5 * w + 1.5 * x - 1.5 * y + 0.5 * z;
    number f1 = w - 2.5 * x + 2 * y - 0.5 * z;
    number f2 = -0.5 * w + 0.5 * y;
    return f0 * a * a2 + f1 * a2 + f2 * a + x;
}

inline number spline6interp(number a, number y0, number y1, number y2, number y3, number y4, number y5) {
    number ym2py2 = y0 + y4;
    number ym1py1 = y1 + y3;
    number y2mym2 = y4 - y0;
    number y1mym1 = y3 - y1;
    number sixthym1py1 = (number)1 / (number)6.0 * ym1py1;
    number c0 = (number)1 / (number)120.0 * ym2py2 + (number)13 / (number)60.0 * ym1py1 + (number)11 / (number)20.0 * y2;
    number c1 = (number)1 / (number)24.0 * y2mym2 + (number)5 / (number)12.0 * y1mym1;
    number c2 = (number)1 / (number)12.0 * ym2py2 + sixthym1py1 - (number)1 / (number)2.0 * y2;
    number c3 = (number)1 / (number)12.0 * y2mym2 - (number)1 / (number)6.0 * y1mym1;
    number c4 = (number)1 / (number)24.0 * ym2py2 - sixthym1py1 + (number)1 / (number)4.0 * y2;
    number c5 = (number)1 / (number)120.0 * (y5 - y0) + (number)1 / (number)24.0 * (y1 - y4) + (number)1 / (number)12.0 * (y3 - y2);
    return ((((c5 * a + c4) * a + c3) * a + c2) * a + c1) * a + c0;
}

inline number cosT8(number r) {
    number t84 = 56.0;
    number t83 = 1680.0;
    number t82 = 20160.0;
    number t81 = 2.4801587302e-05;
    number t73 = 42.0;
    number t72 = 840.0;
    number t71 = 1.9841269841e-04;

    if (r < 0.785398163397448309615660845819875721 && r > -0.785398163397448309615660845819875721) {
        number rr = r * r;
        return 1.0 - rr * t81 * (t82 - rr * (t83 - rr * (t84 - rr)));
    } else if (r > 0.0) {
        r -= 1.57079632679489661923132169163975144;
        number rr = r * r;
        return -r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    } else {
        r += 1.57079632679489661923132169163975144;
        number rr = r * r;
        return r * (1.0 - t71 * rr * (t72 - rr * (t73 - rr)));
    }
}

inline number cosineinterp(number frac, number x, number y) {
    number a2 = (1.0 - this->cosT8(frac * 3.14159265358979323846)) / (number)2.0;
    return x * (1.0 - a2) + y * a2;
}

inline number intnum(const number value) {
    return trunc(value);
}

template<typename BUFFERTYPE> number dim(BUFFERTYPE& buffer) {
    return buffer->getSize();
}

template<typename BUFFERTYPE> number channels(BUFFERTYPE& buffer) {
    return buffer->getChannels();
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

template<typename BUFFERTYPE> void poke_default(
    BUFFERTYPE& buffer,
    SampleValue value,
    SampleValue sampleIndex,
    Int channel,
    number overdub
) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());

    if (bufferSize > 0 && (5 != 5 || (sampleIndex >= 0 && sampleIndex < bufferSize)) && (5 != 5 || (channel >= 0 && channel < bufferChannels))) {
        if (overdub != 0) {
            number currentValue = buffer->getSample(channel, sampleIndex);

            {
                value = value + currentValue * overdub;
            }
        }

        buffer->setSample(channel, sampleIndex, value);
        buffer->setTouched(true);
    }
}

template<typename BUFFERTYPE> array<SampleValue, 1 + 1> peek_default(BUFFERTYPE& buffer, SampleValue sampleIndex, Index channelOffset) {
    number bufferSize = buffer->getSize();
    const Index bufferChannels = (const Index)(buffer->getChannels());
    constexpr int ___N2 = 1 + 1;
    array<SampleValue, ___N2> out = FIXEDSIZEARRAYINIT(1 + 1);

    if (bufferSize == 0 || (5 == 5 && (sampleIndex < 0 || sampleIndex >= bufferSize))) {
        return out;
    } else {
        for (Index channel = 0; channel < 1; channel++) {
            Index channelIndex = (Index)(channel + channelOffset);

            {
                if (channelIndex >= bufferChannels || channelIndex < 0) {
                    out[(Index)channel] = 0;
                    continue;
                }
            }

            SampleValue bufferreadsample_result;

            {
                auto& __buffer = buffer;

                if (sampleIndex < 0.0) {
                    bufferreadsample_result = 0.0;
                }

                SampleIndex truncIndex = (SampleIndex)(trunc(sampleIndex));

                {
                    bufferreadsample_result = __buffer->getSample(channelIndex, truncIndex);
                }
            }

            out[(Index)channel] = bufferreadsample_result;
        }

        out[1] = sampleIndex;
        return out;
    }
}

number fromnormalized(Index index, number normalizedValue) {
    return this->convertFromNormalizedParameterValue(index, normalizedValue);
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        this->getEngine()->presetTouched();
        this->param_01_lastValue = this->param_01_value;
    }

    this->expr_04_in1_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        this->getEngine()->presetTouched();
        this->param_02_lastValue = this->param_02_value;
    }

    this->p_01_in7_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        this->getEngine()->presetTouched();
        this->param_03_lastValue = this->param_03_value;
    }

    this->p_01_in6_number_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        this->getEngine()->presetTouched();
        this->param_04_lastValue = this->param_04_value;
    }

    this->expr_13_in1_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        this->getEngine()->presetTouched();
        this->param_05_lastValue = this->param_05_value;
    }

    this->expr_09_in1_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        this->getEngine()->presetTouched();
        this->param_06_lastValue = this->param_06_value;
    }

    this->p_01_in5_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        this->getEngine()->presetTouched();
        this->param_07_lastValue = this->param_07_value;
    }

    this->expr_14_in1_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        this->getEngine()->presetTouched();
        this->param_08_lastValue = this->param_08_value;
    }

    this->p_01_in3_number_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        this->getEngine()->presetTouched();
        this->param_09_lastValue = this->param_09_value;
    }

    this->p_01_in2_number_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

template<typename LISTTYPE> void message_03_listin_list_set(const LISTTYPE& v) {
    this->message_03_set_set(v);
}

void message_03_listin_number_set(number v) {
    this->message_03_set_set(v);
}

void message_03_listin_bang_bang() {
    this->message_03_trigger_bang();
}

void loadbang_01_startupbang_bang() {
    this->loadbang_01_output_bang();
}

void numbertilde_01_sig_number_set(number v) {
    this->numbertilde_01_outValue = v;
}

template<typename LISTTYPE> void numbertilde_01_sig_list_set(const LISTTYPE& v) {
    this->numbertilde_01_outValue = v[0];
}

void numbertilde_01_mode_set(number v) {
    if (v == 1) {
        this->numbertilde_01_currentMode = 0;
    } else if (v == 2) {
        this->numbertilde_01_currentMode = 1;
    }
}

void numbertilde_02_sig_number_set(number v) {
    this->numbertilde_02_outValue = v;
}

template<typename LISTTYPE> void numbertilde_02_sig_list_set(const LISTTYPE& v) {
    this->numbertilde_02_outValue = v[0];
}

void numbertilde_02_mode_set(number v) {
    if (v == 1) {
        this->numbertilde_02_currentMode = 0;
    } else if (v == 2) {
        this->numbertilde_02_currentMode = 1;
    }
}

void numbertilde_01_value_set(number v) {
    this->recordtilde_01_record_set(v);
}

void numbertilde_02_value_set(number v) {
    this->route_01_input_number_set(v);
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 5; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillRNBODefaultSinus(DataRef& ref) {
    SampleBuffer buffer(ref);
    number bufsize = buffer->getSize();

    for (Index i = 0; i < bufsize; i++) {
        buffer[i] = rnbo_cos(i * 3.14159265358979323846 * 2. / bufsize);
    }
}

void fillDataRef(DataRefIndex index, DataRef& ref) {
    switch (index) {
    case 1:
        {
        this->fillRNBODefaultSinus(ref);
        break;
        }
    }
}

void zeroDataRef(DataRef& ref) {
    ref->setZero();
}

void allocateDataRefs() {
    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->allocateDataRefs();
    }

    this->data_02_buffer->requestSize(this->mstosamps(1000), 1);
    this->data_02_buffer->setSampleRate(this->sr);
    this->gen_03_cycle_4_buffer->requestSize(16384, 1);
    this->gen_03_cycle_4_buffer->setSampleRate(this->sr);
    this->gen_03_cycle_10_buffer->requestSize(16384, 1);
    this->gen_03_cycle_10_buffer->setSampleRate(this->sr);
    this->gen_06_norm_buffer->requestSize(2048, 1);
    this->gen_06_norm_buffer->setSampleRate(this->sr);
    this->gen_06_diff_buffer->requestSize(2048, 1);
    this->gen_06_diff_buffer->setSampleRate(this->sr);
    this->gen_06_yin_buffer->requestSize(4096, 1);
    this->gen_06_yin_buffer->setSampleRate(this->sr);
    this->recordtilde_01_buffer = this->recordtilde_01_buffer->allocateIfNeeded();
    this->data_02_buffer = this->data_02_buffer->allocateIfNeeded();

    if (this->sample->hasRequestedSize()) {
        if (this->sample->wantsFill())
            this->zeroDataRef(this->sample);

        this->getEngine()->sendDataRefUpdated(0);
    }

    this->gen_03_cycle_4_buffer = this->gen_03_cycle_4_buffer->allocateIfNeeded();
    this->gen_03_cycle_10_buffer = this->gen_03_cycle_10_buffer->allocateIfNeeded();

    if (this->RNBODefaultSinus->hasRequestedSize()) {
        if (this->RNBODefaultSinus->wantsFill())
            this->fillRNBODefaultSinus(this->RNBODefaultSinus);

        this->getEngine()->sendDataRefUpdated(1);
    }

    this->gen_06_norm_buffer = this->gen_06_norm_buffer->allocateIfNeeded();

    if (this->norm_buffer->hasRequestedSize()) {
        if (this->norm_buffer->wantsFill())
            this->zeroDataRef(this->norm_buffer);

        this->getEngine()->sendDataRefUpdated(2);
    }

    this->gen_06_diff_buffer = this->gen_06_diff_buffer->allocateIfNeeded();

    if (this->diff_buffer->hasRequestedSize()) {
        if (this->diff_buffer->wantsFill())
            this->zeroDataRef(this->diff_buffer);

        this->getEngine()->sendDataRefUpdated(3);
    }

    this->gen_06_yin_buffer = this->gen_06_yin_buffer->allocateIfNeeded();

    if (this->yin_buffer->hasRequestedSize()) {
        if (this->yin_buffer->wantsFill())
            this->zeroDataRef(this->yin_buffer);

        this->getEngine()->sendDataRefUpdated(4);
    }
}

void initializeObjects() {
    this->message_03_init();
    this->gen_02_switch_init();
    this->numbertilde_01_init();
    this->data_02_init();
    this->gen_04_latch_0_init();
    this->ftom_tilde_01_innerScala_init();
    this->ftom_tilde_01_init();
    this->numbertilde_02_init();
    this->gen_06_writepos_init();
    this->gen_06_framecount_init();
    this->gen_06_detected_tau_init();
    this->gen_06_min_value_init();
    this->gen_06_prev_tau1_init();
    this->gen_06_prev_tau2_init();
    this->gen_06_prev_tau3_init();
    this->gen_06_refined_tau_init();
    this->gen_06_prev_freq_init();
    this->gen_06_prev_conf_init();
    this->gen_06_freq_buffer1_init();
    this->gen_06_freq_buffer2_init();
    this->gen_06_freq_buffer3_init();
    this->gen_06_last_valid_freq_init();
    this->gen_06_hold_counter_init();
    this->gen_06_gate_state_init();
    this->gen_06_low_conf_freq_init();
    this->gen_06_low_conf_count_init();
    this->midinotecontroller_01_init();

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->initializeObjects();
    }
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {
    for (Index i = 0; i < 8; i++) {

        this->p_01[(Index)i]->setEngineAndPatcher(this->getEngine(), this);
        this->p_01[(Index)i]->initialize();
        this->p_01[(Index)i]->setParameterOffset(this->getParameterOffset(this->p_01[0]));
        this->p_01[(Index)i]->setVoiceIndex(i + 1);
    }
}

ParameterIndex getParameterOffset(BaseInterface& subpatcher) const {
    if (addressOf(subpatcher) == addressOf(this->p_01[0]))
        return 9;

    return 0;
}

void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
    RNBO_UNUSED(hasValue);
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case -871642103:
        {
        this->loadbang_01_startupbang_bang();
        break;
        }
    case 2098551528:
        {
        this->numbertilde_01_value_set(value);
        break;
        }
    case -1494586265:
        {
        this->numbertilde_02_value_set(value);
        break;
        }
    }
}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);

    for (Index i = 0; i < 8; i++) {
        this->p_01[i]->startup();
    }

    this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;

    {
        this->scheduleParamInit(0, 13);
    }

    {
        this->scheduleParamInit(1, 12);
    }

    {
        this->scheduleParamInit(2, 11);
    }

    {
        this->scheduleParamInit(3, 99);
    }

    {
        this->scheduleParamInit(4, 14);
    }

    {
        this->scheduleParamInit(5, 4);
    }

    {
        this->scheduleParamInit(6, 3);
    }

    {
        this->scheduleParamInit(7, 2);
    }

    {
        this->scheduleParamInit(8, 1);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in9_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_04_out1_number_set(v);
        }
    }
}

void expr_08_out1_set(number v) {
    this->expr_08_out1 = v;
    this->p_01_in9_number_set(this->expr_08_out1);
}

void expr_08_in1_set(number in1) {
    this->expr_08_in1 = in1;
    this->expr_08_out1_set(fixnan(rnbo_pow(this->expr_08_in1, this->expr_08_in2)));//#map:pow_obj-44:1
}

void expr_04_out1_set(number v) {
    this->expr_04_out1 = v;
    this->expr_08_in1_set(this->expr_04_out1);
}

void expr_04_in1_set(number in1) {
    this->expr_04_in1 = in1;
    this->expr_04_out1_set(this->expr_04_in1 * this->expr_04_in2);//#map:*_obj-15:1
}

number param_02_value_constrain(number v) const {
    v = (v > 500 ? 500 : (v < 10 ? 10 : v));
    return v;
}

void p_01_in7_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_02_out1_number_set(v);
        }
    }
}

number param_03_value_constrain(number v) const {
    v = (v > 60 ? 60 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in6_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_01_out1_number_set(v);
        }
    }
}

number param_04_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void gen_03_in5_set(number v) {
    this->gen_03_in5 = v;
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->gen_03_in5_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:*_obj-9:1
}

number param_05_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in11_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_06_out1_number_set(v);
        }
    }
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->p_01_in11_number_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:*_obj-4:1
}

number param_06_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 10 ? 10 : v));
    return v;
}

void p_01_in5_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_11_out1_number_set(v);
        }
    }
}

number param_07_value_constrain(number v) const {
    v = (v > 100 ? 100 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in4_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_09_out1_number_set(v);
        }
    }
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->p_01_in4_number_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:*_obj-123:1
}

number param_08_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 10 ? 10 : v));
    return v;
}

void p_01_in3_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_08_out1_number_set(v);
        }
    }
}

number param_09_value_constrain(number v) const {
    v = (v > 2000 ? 2000 : (v < 0 ? 0 : v));
    return v;
}

void p_01_in2_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_07_out1_number_set(v);
        }
    }
}

template<typename LISTTYPE> void message_03_set_set(const LISTTYPE& v) {
    this->message_03_set = jsCreateListCopy(v);
}

template<typename LISTTYPE> void p_01_in10_list_set(const LISTTYPE& v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_05_out1_list_set(v);
        }
    }
}

template<typename LISTTYPE> void p_01_in8_list_set(const LISTTYPE& v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_03_out1_list_set(v);
        }
    }
}

template<typename LISTTYPE> void message_03_out_set(const LISTTYPE& v) {
    this->p_01_in10_list_set(v);
    this->p_01_in8_list_set(v);
}

void message_03_trigger_bang() {
    if ((bool)(this->message_03_set->length) || (bool)(false)) {
        this->message_03_out_set(this->message_03_set);
    }
}

void loadbang_01_output_bang() {
    this->message_03_trigger_bang();
}

void midinotecontroller_01_currenttarget_set(number v) {
    this->midinotecontroller_01_currenttarget = v;
}

void p_01_target_set(number v) {
    this->p_01_target = v;
    this->midinotecontroller_01_currenttarget_set(v);
}

void midinotecontroller_01_target_set(number v) {
    this->p_01_target_set(v);
}

void p_01_midiininternal_set(number v) {
    Index sendlen = 0;
    this->p_01_currentStatus = parseMidi(this->p_01_currentStatus, (Int)(v), this->p_01_mididata[0]);

    switch ((int)this->p_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        this->p_01_mididata[0] = (uint8_t)(v);
        this->p_01_mididata[1] = 0;
        break;
        }
    case MIDI_SecondByteReceived:
    case MIDI_ProgramChange:
    case MIDI_ChannelPressure:
        {
        this->p_01_mididata[1] = (uint8_t)(v);

        if (this->p_01_currentStatus == MIDI_ProgramChange || this->p_01_currentStatus == MIDI_ChannelPressure) {
            sendlen = 2;
        }

        break;
        }
    case MIDI_NoteOff:
    case MIDI_NoteOn:
    case MIDI_Aftertouch:
    case MIDI_CC:
    case MIDI_PitchBend:
    default:
        {
        this->p_01_mididata[2] = (uint8_t)(v);
        sendlen = 3;
        break;
        }
    }

    if (sendlen > 0) {
        number i;

        if (this->p_01_target > 0 && this->p_01_target <= 8) {
            i = this->p_01_target - 1;
            this->p_01[(Index)i]->processMidiEvent(_currentTime, 0, this->p_01_mididata, sendlen);
        } else if (this->p_01_target == 0) {
            for (i = 0; i < 8; i++) {
                this->p_01[(Index)i]->processMidiEvent(_currentTime, 0, this->p_01_mididata, sendlen);
            }
        }
    }
}

void midinotecontroller_01_midiout_set(number v) {
    this->p_01_midiininternal_set(v);
}

void p_01_noteNumber_set(number v) {
    if (this->p_01_target > 0) {
        this->p_01[(Index)(this->p_01_target - 1)]->setNoteNumber((Int)(v));
    }
}

void midinotecontroller_01_noteNumber_set(number v) {
    this->p_01_noteNumber_set(v);
}

template<typename LISTTYPE> void midinotecontroller_01_voicestatus_set(const LISTTYPE& v) {
    if (v[1] == 1) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v[0]);
        this->midinotecontroller_01_noteNumber_set(0);
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

template<typename LISTTYPE> void p_01_voicestatus_set(const LISTTYPE& v) {
    this->midinotecontroller_01_voicestatus_set(v);
}

void p_01_activevoices_set(number ) {}

template<typename LISTTYPE> void p_01_mute_set(const LISTTYPE& v) {
    Index voiceNumber = (Index)(v[0]);
    Index muteState = (Index)(v[1]);

    if (voiceNumber == 0) {
        for (Index i = 0; i < 8; i++) {
            this->p_01[(Index)i]->setIsMuted(muteState);
        }
    } else {
        Index subpatcherIndex = voiceNumber - 1;

        if (subpatcherIndex >= 0 && subpatcherIndex < 8) {
            this->p_01[(Index)subpatcherIndex]->setIsMuted(muteState);
        }
    }

    list tmp = {v[0], v[1]};
    this->p_01_voicestatus_set(tmp);
    this->p_01_activevoices_set(this->p_01_calcActiveVoices());
}

template<typename LISTTYPE> void midinotecontroller_01_mute_set(const LISTTYPE& v) {
    this->p_01_mute_set(v);
}

void midinotecontroller_01_midiin_set(number v) {
    this->midinotecontroller_01_midiin = v;
    Int val = (Int)(v);

    this->midinotecontroller_01_currentStatus = parseMidi(
        this->midinotecontroller_01_currentStatus,
        (Int)(v),
        this->midinotecontroller_01_status
    );

    switch ((int)this->midinotecontroller_01_currentStatus) {
    case MIDI_StatusByteReceived:
        {
        {
            this->midinotecontroller_01_status = val;
            this->midinotecontroller_01_byte1 = -1;
            break;
        }
        }
    case MIDI_SecondByteReceived:
        {
        this->midinotecontroller_01_byte1 = val;
        break;
        }
    case MIDI_NoteOn:
        {
        {
            bool sendnoteoff = true;
            Int target = 1;
            MillisecondTime oldest = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[0]);
            number target_state = this->midinotecontroller_01_voice_state[0];

            for (Int i = 0; i < 8; i++) {
                number candidate_state = this->midinotecontroller_01_voice_state[(Index)i];

                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == this->midinotecontroller_01_byte1 && candidate_state == MIDI_NoteState_On) {
                    sendnoteoff = false;
                    target = i + 1;
                    break;
                }

                if (i > 0) {
                    if (candidate_state != MIDI_NoteState_On || target_state == MIDI_NoteState_On) {
                        MillisecondTime candidate_ontime = (MillisecondTime)(this->midinotecontroller_01_voice_lastontime[(Index)i]);

                        if (candidate_ontime < oldest || (target_state == MIDI_NoteState_On && candidate_state != MIDI_NoteState_On)) {
                            target = i + 1;
                            oldest = candidate_ontime;
                            target_state = candidate_state;
                        }
                    }
                }
            }

            if ((bool)(sendnoteoff))
                this->midinotecontroller_01_sendnoteoff(target);

            Int i = (Int)(target - 1);
            this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_On;
            this->midinotecontroller_01_voice_lastontime[(Index)i] = this->_currentTime;
            this->midinotecontroller_01_voice_notenumber[(Index)i] = this->midinotecontroller_01_byte1;
            this->midinotecontroller_01_voice_channel[(Index)i] = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Index j = 0; j < 128; j++) {
                if (this->midinotecontroller_01_notesdown[(Index)j] == 0) {
                    this->midinotecontroller_01_notesdown[(Index)j] = this->midinotecontroller_01_voice_notenumber[(Index)i];
                    break;
                }
            }

            this->midinotecontroller_01_note_lastvelocity[(Index)this->midinotecontroller_01_voice_notenumber[(Index)i]] = val;
            this->midinotecontroller_01_sendpitchbend(i);
            this->midinotecontroller_01_sendpressure(i);
            this->midinotecontroller_01_sendtimbre(i);
            this->midinotecontroller_01_muteval[0] = target;
            this->midinotecontroller_01_muteval[1] = 0;
            this->midinotecontroller_01_mute_set(this->midinotecontroller_01_muteval);
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(target);
            this->midinotecontroller_01_noteNumber_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);

            this->midinotecontroller_01_midiout_set(
                (BinOpInt)((BinOpInt)MIDI_NoteOnMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
            );

            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
            this->midinotecontroller_01_midiout_set(val);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_NoteOff:
        {
        {
            Int target = 0;
            number notenumber = this->midinotecontroller_01_byte1;
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Int i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_notenumber[(Index)i] == notenumber && this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_On) {
                    target = i + 1;
                    break;
                }
            }

            if (target > 0) {
                Int i = (Int)(target - 1);
                Index j = (Index)(channel);
                bool ignoresustainchannel = true;

                if ((bool)(this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)])) {
                    this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Sustained;
                } else {
                    number currentTarget = this->midinotecontroller_01_currenttarget;
                    this->midinotecontroller_01_target_set(target);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                    this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                    this->midinotecontroller_01_midiout_set(v);
                    this->midinotecontroller_01_target_set(currentTarget);

                    if (this->midinotecontroller_01_currentStatus == MIDI_NoteOff) {
                        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                    }
                }
            } else
                {}

            bool found = false;

            for (Index i = 0; i < 128; i++) {
                if (this->midinotecontroller_01_notesdown[(Index)i] == 0) {
                    break;
                } else if (this->midinotecontroller_01_notesdown[(Index)i] == notenumber) {
                    found = true;
                }

                if ((bool)(found)) {
                    this->midinotecontroller_01_notesdown[(Index)i] = this->midinotecontroller_01_notesdown[(Index)(i + 1)];
                }
            }

            break;
        }
        }
    case MIDI_Aftertouch:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_midiout_set(v);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_CC:
        {
        {
            bool sendToAllVoices = true;

            switch ((int)this->midinotecontroller_01_byte1) {
            case MIDI_CC_Sustain:
                {
                {
                    bool pedaldown = (bool)((val >= 64 ? true : false));
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Index j = (Index)(channel);
                    bool ignoresustainchannel = true;
                    this->midinotecontroller_01_channel_sustain[((bool)(ignoresustainchannel) ? 0 : j)] = pedaldown;

                    if ((bool)(!(bool)(pedaldown))) {
                        for (Index i = 0; i < 8; i++) {
                            if (((bool)(ignoresustainchannel) || this->midinotecontroller_01_voice_channel[(Index)i] == channel) && this->midinotecontroller_01_voice_state[(Index)i] == MIDI_NoteState_Sustained) {
                                number currentTarget = this->midinotecontroller_01_currenttarget;
                                this->midinotecontroller_01_target_set(i + 1);
                                this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)j));
                                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
                                this->midinotecontroller_01_midiout_set(64);
                                this->midinotecontroller_01_target_set(currentTarget);
                                this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
                            }
                        }
                    }

                    break;
                }
                }
            case MIDI_CC_TimbreMSB:
                {
                {
                    number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);
                    Int k = (Int)(v);
                    number timbre = (BinOpInt)(((BinOpInt)((BinOpInt)k & (BinOpInt)0x7F)) << imod_nocast((UBinOpInt)7, 32));
                    this->midinotecontroller_01_channel_timbre[(Index)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F)] = timbre;

                    for (Int i = 0; i < 8; i++) {
                        if (this->midinotecontroller_01_voice_channel[(Index)i] == channel && this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
                            this->midinotecontroller_01_sendtimbre(i);
                        }
                    }

                    sendToAllVoices = false;
                    break;
                }
                }
            case MIDI_CC_TimbreLSB:
                {
                {
                    break;
                }
                }
            case MIDI_CC_AllNotesOff:
                {
                {
                    this->midinotecontroller_01_sendallnotesoff();
                    break;
                }
                }
            }

            if ((bool)(sendToAllVoices)) {
                number currentTarget = this->midinotecontroller_01_currenttarget;
                this->midinotecontroller_01_target_set(0);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
                this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
                this->midinotecontroller_01_midiout_set(v);
                this->midinotecontroller_01_target_set(currentTarget);
            }

            break;
        }
        }
    case MIDI_ProgramChange:
        {
        {
            number currentTarget = this->midinotecontroller_01_currenttarget;
            this->midinotecontroller_01_target_set(0);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_status);
            this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_byte1);
            this->midinotecontroller_01_target_set(currentTarget);
            break;
        }
        }
    case MIDI_ChannelPressure:
        {
        {
            number channel = (BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F);

            for (Int i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    Int k = (Int)(channel);
                    this->midinotecontroller_01_channel_pressure[(Index)k] = v;
                    this->midinotecontroller_01_sendpressure(i);
                }
            }

            break;
        }
        }
    case MIDI_PitchBend:
        {
        {
            number bendamount = (BinOpInt)((BinOpInt)this->midinotecontroller_01_byte1 | (BinOpInt)((BinOpInt)val << imod_nocast((UBinOpInt)7, 32)));
            Int channel = (Int)((BinOpInt)((BinOpInt)this->midinotecontroller_01_status & (BinOpInt)0x0F));
            this->midinotecontroller_01_channel_pitchbend[(Index)channel] = bendamount;

            for (Int i = 0; i < 8; i++) {
                if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off && this->midinotecontroller_01_voice_channel[(Index)i] == channel) {
                    this->midinotecontroller_01_sendpitchbend(i);
                }
            }

            break;
        }
        }
    }
}

void p_01_midiin_set(number v) {
    this->p_01_midiin = v;
    this->midinotecontroller_01_midiin_set(v);
}

void midiin_02_midiout_set(number v) {
    this->p_01_midiin_set(v);
}

void midiin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(port);
    RNBO_UNUSED(channel);
    RNBO_UNUSED(status);
    Index i;

    for (i = 0; i < length; i++) {
        this->midiin_02_midiout_set(data[i]);
    }
}

void ctlin_01_outchannel_set(number ) {}

void ctlin_01_outcontroller_set(number ) {}

void fromnormalized_01_output_set(number v) {
    this->param_01_value_set(v);
}

void fromnormalized_01_input_set(number v) {
    this->fromnormalized_01_output_set(this->fromnormalized(0, v));
}

void expr_05_out1_set(number v) {
    this->expr_05_out1 = v;
    this->fromnormalized_01_input_set(this->expr_05_out1);
}

void expr_05_in1_set(number in1) {
    this->expr_05_in1 = in1;
    this->expr_05_out1_set(this->expr_05_in1 * this->expr_05_in2);//#map:expr_05:1
}

void ctlin_01_value_set(number v) {
    this->expr_05_in1_set(v);
}

void ctlin_01_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_01_channel || this->ctlin_01_channel == -1) && (data[1] == this->ctlin_01_controller || this->ctlin_01_controller == -1)) {
        this->ctlin_01_outchannel_set(channel);
        this->ctlin_01_outcontroller_set(data[1]);
        this->ctlin_01_value_set(data[2]);
        this->ctlin_01_status = 0;
    }
}

void ctlin_02_outchannel_set(number ) {}

void ctlin_02_outcontroller_set(number ) {}

void fromnormalized_02_output_set(number v) {
    this->param_02_value_set(v);
}

void fromnormalized_02_input_set(number v) {
    this->fromnormalized_02_output_set(this->fromnormalized(1, v));
}

void expr_06_out1_set(number v) {
    this->expr_06_out1 = v;
    this->fromnormalized_02_input_set(this->expr_06_out1);
}

void expr_06_in1_set(number in1) {
    this->expr_06_in1 = in1;
    this->expr_06_out1_set(this->expr_06_in1 * this->expr_06_in2);//#map:expr_06:1
}

void ctlin_02_value_set(number v) {
    this->expr_06_in1_set(v);
}

void ctlin_02_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_02_channel || this->ctlin_02_channel == -1) && (data[1] == this->ctlin_02_controller || this->ctlin_02_controller == -1)) {
        this->ctlin_02_outchannel_set(channel);
        this->ctlin_02_outcontroller_set(data[1]);
        this->ctlin_02_value_set(data[2]);
        this->ctlin_02_status = 0;
    }
}

void ctlin_03_outchannel_set(number ) {}

void ctlin_03_outcontroller_set(number ) {}

void fromnormalized_03_output_set(number v) {
    this->param_03_value_set(v);
}

void fromnormalized_03_input_set(number v) {
    this->fromnormalized_03_output_set(this->fromnormalized(2, v));
}

void expr_07_out1_set(number v) {
    this->expr_07_out1 = v;
    this->fromnormalized_03_input_set(this->expr_07_out1);
}

void expr_07_in1_set(number in1) {
    this->expr_07_in1 = in1;
    this->expr_07_out1_set(this->expr_07_in1 * this->expr_07_in2);//#map:expr_07:1
}

void ctlin_03_value_set(number v) {
    this->expr_07_in1_set(v);
}

void ctlin_03_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_03_channel || this->ctlin_03_channel == -1) && (data[1] == this->ctlin_03_controller || this->ctlin_03_controller == -1)) {
        this->ctlin_03_outchannel_set(channel);
        this->ctlin_03_outcontroller_set(data[1]);
        this->ctlin_03_value_set(data[2]);
        this->ctlin_03_status = 0;
    }
}

void ctlin_04_outchannel_set(number ) {}

void ctlin_04_outcontroller_set(number ) {}

void fromnormalized_04_output_set(number v) {
    this->param_04_value_set(v);
}

void fromnormalized_04_input_set(number v) {
    this->fromnormalized_04_output_set(this->fromnormalized(3, v));
}

void expr_10_out1_set(number v) {
    this->expr_10_out1 = v;
    this->fromnormalized_04_input_set(this->expr_10_out1);
}

void expr_10_in1_set(number in1) {
    this->expr_10_in1 = in1;
    this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:expr_10:1
}

void ctlin_04_value_set(number v) {
    this->expr_10_in1_set(v);
}

void ctlin_04_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_04_channel || this->ctlin_04_channel == -1) && (data[1] == this->ctlin_04_controller || this->ctlin_04_controller == -1)) {
        this->ctlin_04_outchannel_set(channel);
        this->ctlin_04_outcontroller_set(data[1]);
        this->ctlin_04_value_set(data[2]);
        this->ctlin_04_status = 0;
    }
}

void ctlin_05_outchannel_set(number ) {}

void ctlin_05_outcontroller_set(number ) {}

void fromnormalized_05_output_set(number v) {
    this->param_05_value_set(v);
}

void fromnormalized_05_input_set(number v) {
    this->fromnormalized_05_output_set(this->fromnormalized(4, v));
}

void expr_11_out1_set(number v) {
    this->expr_11_out1 = v;
    this->fromnormalized_05_input_set(this->expr_11_out1);
}

void expr_11_in1_set(number in1) {
    this->expr_11_in1 = in1;
    this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:expr_11:1
}

void ctlin_05_value_set(number v) {
    this->expr_11_in1_set(v);
}

void ctlin_05_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_05_channel || this->ctlin_05_channel == -1) && (data[1] == this->ctlin_05_controller || this->ctlin_05_controller == -1)) {
        this->ctlin_05_outchannel_set(channel);
        this->ctlin_05_outcontroller_set(data[1]);
        this->ctlin_05_value_set(data[2]);
        this->ctlin_05_status = 0;
    }
}

void ctlin_06_outchannel_set(number ) {}

void ctlin_06_outcontroller_set(number ) {}

void fromnormalized_06_output_set(number v) {
    this->param_06_value_set(v);
}

void fromnormalized_06_input_set(number v) {
    this->fromnormalized_06_output_set(this->fromnormalized(5, v));
}

void expr_12_out1_set(number v) {
    this->expr_12_out1 = v;
    this->fromnormalized_06_input_set(this->expr_12_out1);
}

void expr_12_in1_set(number in1) {
    this->expr_12_in1 = in1;
    this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:expr_12:1
}

void ctlin_06_value_set(number v) {
    this->expr_12_in1_set(v);
}

void ctlin_06_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_06_channel || this->ctlin_06_channel == -1) && (data[1] == this->ctlin_06_controller || this->ctlin_06_controller == -1)) {
        this->ctlin_06_outchannel_set(channel);
        this->ctlin_06_outcontroller_set(data[1]);
        this->ctlin_06_value_set(data[2]);
        this->ctlin_06_status = 0;
    }
}

void ctlin_07_outchannel_set(number ) {}

void ctlin_07_outcontroller_set(number ) {}

void fromnormalized_07_output_set(number v) {
    this->param_07_value_set(v);
}

void fromnormalized_07_input_set(number v) {
    this->fromnormalized_07_output_set(this->fromnormalized(6, v));
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->fromnormalized_07_input_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 * this->expr_15_in2);//#map:expr_15:1
}

void ctlin_07_value_set(number v) {
    this->expr_15_in1_set(v);
}

void ctlin_07_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_07_channel || this->ctlin_07_channel == -1) && (data[1] == this->ctlin_07_controller || this->ctlin_07_controller == -1)) {
        this->ctlin_07_outchannel_set(channel);
        this->ctlin_07_outcontroller_set(data[1]);
        this->ctlin_07_value_set(data[2]);
        this->ctlin_07_status = 0;
    }
}

void ctlin_08_outchannel_set(number ) {}

void ctlin_08_outcontroller_set(number ) {}

void fromnormalized_08_output_set(number v) {
    this->param_08_value_set(v);
}

void fromnormalized_08_input_set(number v) {
    this->fromnormalized_08_output_set(this->fromnormalized(7, v));
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->fromnormalized_08_input_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 * this->expr_16_in2);//#map:expr_16:1
}

void ctlin_08_value_set(number v) {
    this->expr_16_in1_set(v);
}

void ctlin_08_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_08_channel || this->ctlin_08_channel == -1) && (data[1] == this->ctlin_08_controller || this->ctlin_08_controller == -1)) {
        this->ctlin_08_outchannel_set(channel);
        this->ctlin_08_outcontroller_set(data[1]);
        this->ctlin_08_value_set(data[2]);
        this->ctlin_08_status = 0;
    }
}

void ctlin_09_outchannel_set(number ) {}

void ctlin_09_outcontroller_set(number ) {}

void fromnormalized_09_output_set(number v) {
    this->param_09_value_set(v);
}

void fromnormalized_09_input_set(number v) {
    this->fromnormalized_09_output_set(this->fromnormalized(8, v));
}

void expr_17_out1_set(number v) {
    this->expr_17_out1 = v;
    this->fromnormalized_09_input_set(this->expr_17_out1);
}

void expr_17_in1_set(number in1) {
    this->expr_17_in1 = in1;
    this->expr_17_out1_set(this->expr_17_in1 * this->expr_17_in2);//#map:expr_17:1
}

void ctlin_09_value_set(number v) {
    this->expr_17_in1_set(v);
}

void ctlin_09_midihandler(int status, int channel, int port, ConstByteArray data, Index length) {
    RNBO_UNUSED(length);
    RNBO_UNUSED(port);

    if (status == 0xB0 && (channel == this->ctlin_09_channel || this->ctlin_09_channel == -1) && (data[1] == this->ctlin_09_controller || this->ctlin_09_controller == -1)) {
        this->ctlin_09_outchannel_set(channel);
        this->ctlin_09_outcontroller_set(data[1]);
        this->ctlin_09_value_set(data[2]);
        this->ctlin_09_status = 0;
    }
}

void p_01_perform(SampleValue * out1, SampleValue * out2, SampleValue * out3, Index n) {
    // subpatcher: voice
    SampleArray<3> outs = {out1, out2, out3};

    for (number chan = 0; chan < 3; chan++)
        zeroSignal(outs[(Index)chan], n);

    for (Index i = 0; i < 8; i++)
        this->p_01[(Index)i]->process(nullptr, 0, outs, 3, n);
}

void signalsend_01_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_03_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalsend_02_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_04_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void gen_02_perform(const Sample * in1, SampleValue * out1, Index n) {
    auto __gen_02_switch_value = this->gen_02_switch_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number amplitude_0 = in1[(Index)i];

        if (amplitude_0 == 0) {
            __gen_02_switch_value = 1;
        } else {
            __gen_02_switch_value = 0;
        }

        number expr_1_1 = __gen_02_switch_value;
        out1[(Index)i] = expr_1_1;
    }

    this->gen_02_switch_value = __gen_02_switch_value;
}

void recordtilde_01_record_set(number v) {
    this->recordtilde_01_record = v;

    if ((bool)(v)) {
        this->recordtilde_01_lastRecord = 0;
    }
}

void numbertilde_01_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __numbertilde_01_currentIntervalInSamples = this->numbertilde_01_currentIntervalInSamples;
    auto __numbertilde_01_lastValue = this->numbertilde_01_lastValue;
    auto __numbertilde_01_currentInterval = this->numbertilde_01_currentInterval;
    auto __numbertilde_01_rampInSamples = this->numbertilde_01_rampInSamples;
    auto __numbertilde_01_outValue = this->numbertilde_01_outValue;
    auto __numbertilde_01_currentMode = this->numbertilde_01_currentMode;
    number monitorvalue = input_signal[0];

    for (Index i = 0; i < n; i++) {
        if (__numbertilde_01_currentMode == 0) {
            output[(Index)i] = this->numbertilde_01_smooth_next(
                __numbertilde_01_outValue,
                __numbertilde_01_rampInSamples,
                __numbertilde_01_rampInSamples
            );
        } else {
            output[(Index)i] = input_signal[(Index)i];
        }
    }

    __numbertilde_01_currentInterval -= n;

    if (monitorvalue != __numbertilde_01_lastValue && __numbertilde_01_currentInterval <= 0) {
        __numbertilde_01_currentInterval = __numbertilde_01_currentIntervalInSamples;

        this->getEngine()->scheduleClockEventWithValue(
            this,
            2098551528,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            monitorvalue
        );;

        __numbertilde_01_lastValue = monitorvalue;
        ;
    }

    this->numbertilde_01_currentInterval = __numbertilde_01_currentInterval;
    this->numbertilde_01_lastValue = __numbertilde_01_lastValue;
}

void signalsend_03_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_05_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void gen_06_perform(
    const Sample * in1,
    number minfreq,
    number maxfreq,
    number window_size,
    number threshold,
    number smooth_factor,
    number confidence_threshold,
    number hold_time,
    number hysteresis,
    number octave_correct,
    number process_rate,
    SampleValue * out1,
    Index n
) {
    RNBO_UNUSED(process_rate);
    RNBO_UNUSED(octave_correct);
    RNBO_UNUSED(hysteresis);
    RNBO_UNUSED(hold_time);
    RNBO_UNUSED(confidence_threshold);
    RNBO_UNUSED(smooth_factor);
    RNBO_UNUSED(threshold);
    RNBO_UNUSED(window_size);
    RNBO_UNUSED(maxfreq);
    RNBO_UNUSED(minfreq);
    auto __gen_06_hold_counter_value = this->gen_06_hold_counter_value;
    auto __gen_06_gate_state_value = this->gen_06_gate_state_value;
    auto __gen_06_prev_freq_value = this->gen_06_prev_freq_value;
    auto __gen_06_freq_buffer1_value = this->gen_06_freq_buffer1_value;
    auto __gen_06_freq_buffer2_value = this->gen_06_freq_buffer2_value;
    auto __gen_06_freq_buffer3_value = this->gen_06_freq_buffer3_value;
    auto __gen_06_prev_conf_value = this->gen_06_prev_conf_value;
    auto __gen_06_last_valid_freq_value = this->gen_06_last_valid_freq_value;
    auto __gen_06_low_conf_freq_value = this->gen_06_low_conf_freq_value;
    auto __gen_06_low_conf_count_value = this->gen_06_low_conf_count_value;
    auto __gen_06_refined_tau_value = this->gen_06_refined_tau_value;
    auto __gen_06_min_value_value = this->gen_06_min_value_value;
    auto __gen_06_detected_tau_value = this->gen_06_detected_tau_value;
    auto __gen_06_prev_tau3_value = this->gen_06_prev_tau3_value;
    auto __gen_06_prev_tau2_value = this->gen_06_prev_tau2_value;
    auto __gen_06_prev_tau1_value = this->gen_06_prev_tau1_value;
    auto __gen_06_framecount_value = this->gen_06_framecount_value;
    auto __gen_06_writepos_value = this->gen_06_writepos_value;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        auto norm_buffer_dim_1_0 = this->dim(this->gen_06_norm_buffer);
        auto norm_buffer_chans_2_1 = this->channels(this->gen_06_norm_buffer);
        auto diff_buffer_dim_3_2 = this->dim(this->gen_06_diff_buffer);
        auto diff_buffer_chans_4_3 = this->channels(this->gen_06_diff_buffer);
        auto yin_buffer_dim_5_4 = this->dim(this->gen_06_yin_buffer);
        auto yin_buffer_chans_6_5 = this->channels(this->gen_06_yin_buffer);
        number process_6 = 0;
        number start_pos_7 = 0;
        number tau_8 = 0;
        number diff_sum_9 = 0;
        number j_10 = 0;
        number idx1_11 = 0;
        number idx2_12 = 0;
        number s1_13 = 0;
        number s2_14 = 0;
        number diff_15 = 0;
        number step_16 = 0;
        number running_sum_17 = 0;
        number d_tau_18 = 0;
        number d_prime_19 = 0;
        number best_tau_20 = 0;
        number min_val_21 = 0;
        number global_min_22 = 0;
        number global_tau_23 = 0;
        number search_end_24 = 0;
        number i_25 = 0;
        number val_26 = 0;
        number avg_tau_27 = 0;
        number x0_28 = 0;
        number x1_29 = 0;
        number x2_30 = 0;
        number y0_31 = 0;
        number y1_32 = 0;
        number y2_33 = 0;
        number a_34 = 0;
        number b_35 = 0;
        number x_offset_36 = 0;
        number freq_37 = 0;
        number ratio_38 = 0;
        number smoothed_freq_39 = 0;
        number temp_40 = 0;
        number output_freq_41 = 0;
        number prev_val_42 = 0;
        number next_val_43 = 0;
        auto bufsize_7_44 = this->dim(this->gen_06_yin_buffer);
        number sr_8_45 = this->sr;
        auto winsize_9_46 = this->minimum(1024, bufsize_7_44 / (number)2);
        auto minlag_10_47 = this->maximum(2, rnbo_floor(sr_8_45 / (number)2000));
        auto maxlag_11_48 = this->minimum(rnbo_floor(sr_8_45 / (number)65), winsize_9_46 - 1);
        this->poke_default(this->gen_06_yin_buffer, in1[(Index)i], __gen_06_writepos_value, 0, 0);
        __gen_06_writepos_value = this->wrap(__gen_06_writepos_value + 1, 0, bufsize_7_44);
        __gen_06_framecount_value = __gen_06_framecount_value + 1;

        if (__gen_06_framecount_value >= 256) {
            __gen_06_framecount_value = 0;
            process_6 = 1;
        } else {
            process_6 = 0;
        }

        if ((bool)(process_6)) {
            start_pos_7 = this->wrap(__gen_06_writepos_value - winsize_9_46, 0, bufsize_7_44);

            for (number tau_8 = 0; tau_8 <= maxlag_11_48; tau_8 = tau_8 + 2) {
                diff_sum_9 = 0;

                if (tau_8 < 50) {
                    step_16 = 2;
                } else if (tau_8 < 200) {
                    step_16 = 4;
                } else {
                    step_16 = 8;
                }

                for (number j_10 = 0; j_10 < winsize_9_46 - tau_8; j_10 = j_10 + step_16) {
                    idx1_11 = this->wrap(start_pos_7 + j_10, 0, bufsize_7_44);
                    idx2_12 = this->wrap(start_pos_7 + j_10 + tau_8, 0, bufsize_7_44);
                    auto result_49 = this->peek_default(this->gen_06_yin_buffer, idx1_11, 0);
                    s1_13 = result_49[0];
                    auto result_50 = this->peek_default(this->gen_06_yin_buffer, idx2_12, 0);
                    s2_14 = result_50[0];
                    diff_15 = s1_13 - s2_14;
                    diff_sum_9 = diff_sum_9 + diff_15 * diff_15;
                }

                diff_sum_9 = diff_sum_9 * step_16;
                this->poke_default(this->gen_06_diff_buffer, diff_sum_9, tau_8, 0, 0);
            }

            for (number tau_8 = 1; tau_8 < maxlag_11_48; tau_8 = tau_8 + 2) {
                auto result_51 = this->peek_default(this->gen_06_diff_buffer, tau_8 - 1, 0);
                prev_val_42 = result_51[0];
                auto result_52 = this->peek_default(this->gen_06_diff_buffer, tau_8 + 1, 0);
                next_val_43 = result_52[0];

                this->poke_default(
                    this->gen_06_diff_buffer,
                    (prev_val_42 + next_val_43) / (number)2,
                    tau_8,
                    0,
                    0
                );
            }

            running_sum_17 = 0;

            for (number tau_8 = 1; tau_8 <= maxlag_11_48; tau_8 = tau_8 + 1) {
                auto result_53 = this->peek_default(this->gen_06_diff_buffer, tau_8, 0);
                d_tau_18 = result_53[0];
                running_sum_17 = running_sum_17 + d_tau_18;

                if (tau_8 == 1) {
                    d_prime_19 = 1;
                } else {
                    if (running_sum_17 > 0) {
                        d_prime_19 = (running_sum_17 == 0. ? 0. : d_tau_18 * tau_8 / running_sum_17);
                    } else {
                        d_prime_19 = 1;
                    }
                }

                this->poke_default(this->gen_06_norm_buffer, d_prime_19, tau_8, 0, 0);
            }

            this->poke_default(this->gen_06_norm_buffer, 1, 0, 0, 0);
            min_val_21 = 1;
            best_tau_20 = 0;
            global_min_22 = 1;
            global_tau_23 = 0;

            for (number tau_8 = minlag_10_47; tau_8 < maxlag_11_48; tau_8 = tau_8 + 1) {
                auto result_54 = this->peek_default(this->gen_06_norm_buffer, tau_8, 0);
                d_prime_19 = result_54[0];

                if (d_prime_19 < global_min_22) {
                    global_min_22 = d_prime_19;
                    global_tau_23 = tau_8;
                }

                if (best_tau_20 == 0 && d_prime_19 < 0.1) {
                    min_val_21 = d_prime_19;
                    best_tau_20 = tau_8;
                    search_end_24 = this->minimum(tau_8 + 30, maxlag_11_48);

                    for (number i_25 = tau_8; i_25 < search_end_24; i_25 = i_25 + 1) {
                        auto result_55 = this->peek_default(this->gen_06_norm_buffer, i_25, 0);
                        val_26 = result_55[0];

                        if (val_26 < min_val_21) {
                            min_val_21 = val_26;
                            best_tau_20 = i_25;
                        }
                    }

                    break;
                }
            }

            if (best_tau_20 == 0 && global_min_22 < 0.1 * 2) {
                best_tau_20 = global_tau_23;
                min_val_21 = global_min_22;
            }

            if (best_tau_20 > 0) {
                avg_tau_27 = (__gen_06_prev_tau1_value + __gen_06_prev_tau2_value + __gen_06_prev_tau3_value) / (number)3;

                if (avg_tau_27 > 0 && rnbo_abs(best_tau_20 - avg_tau_27) > avg_tau_27 * 0.5 && min_val_21 > 0.05)
                    {} else {
                    __gen_06_detected_tau_value = best_tau_20;
                    __gen_06_min_value_value = min_val_21;
                }

                __gen_06_prev_tau3_value = __gen_06_prev_tau2_value;
                __gen_06_prev_tau2_value = __gen_06_prev_tau1_value;
                __gen_06_prev_tau1_value = best_tau_20;
            }

            if (__gen_06_detected_tau_value > minlag_10_47 && __gen_06_detected_tau_value < maxlag_11_48 - 1) {
                x0_28 = __gen_06_detected_tau_value - 1;
                x1_29 = __gen_06_detected_tau_value;
                x2_30 = __gen_06_detected_tau_value + 1;
                auto result_56 = this->peek_default(this->gen_06_norm_buffer, x0_28, 0);
                y0_31 = result_56[0];
                auto result_57 = this->peek_default(this->gen_06_norm_buffer, x1_29, 0);
                y1_32 = result_57[0];
                auto result_58 = this->peek_default(this->gen_06_norm_buffer, x2_30, 0);
                y2_33 = result_58[0];

                if (y1_32 < y0_31 && y1_32 < y2_33) {
                    a_34 = (y0_31 - 2 * y1_32 + y2_33) / (number)2;
                    b_35 = (y2_33 - y0_31) / (number)2;

                    if (rnbo_abs(a_34) > 0.0001) {
                        x_offset_36 = (2 * a_34 == 0. ? 0. : -b_35 / (2 * a_34));
                        x_offset_36 = (x_offset_36 > 0.5 ? 0.5 : (x_offset_36 < -0.5 ? -0.5 : x_offset_36));
                        __gen_06_refined_tau_value = __gen_06_detected_tau_value + x_offset_36;
                    } else {
                        __gen_06_refined_tau_value = __gen_06_detected_tau_value;
                    }
                } else {
                    __gen_06_refined_tau_value = __gen_06_detected_tau_value;
                }
            } else {
                __gen_06_refined_tau_value = __gen_06_detected_tau_value;
            }
        }

        number confidence_12_59 = 0;

        if (__gen_06_min_value_value < 0.01) {
            confidence_12_59 = 1;
        } else if (__gen_06_min_value_value < 0.05) {
            confidence_12_59 = 0.9;
        } else if (__gen_06_min_value_value < 0.1) {
            confidence_12_59 = 0.7;
        } else if (__gen_06_min_value_value < 0.2) {
            confidence_12_59 = 0.5;
        } else {
            confidence_12_59 = 1 - __gen_06_min_value_value;
        }

        if (__gen_06_refined_tau_value > 10 && __gen_06_refined_tau_value < 2000) {
            freq_37 = (__gen_06_refined_tau_value == 0. ? 0. : sr_8_45 / __gen_06_refined_tau_value);
            freq_37 = (freq_37 > 3000 ? 3000 : (freq_37 < 50 ? 50 : freq_37));
        } else {
            freq_37 = 0;
        }

        if (1 > 0 && freq_37 > 0) {
            if (confidence_12_59 > 0.4 && confidence_12_59 < 0.6) {
                __gen_06_low_conf_count_value = __gen_06_low_conf_count_value + 1;
                __gen_06_low_conf_freq_value = freq_37;

                if (__gen_06_low_conf_count_value > 3 && __gen_06_last_valid_freq_value > 0) {
                    ratio_38 = (__gen_06_last_valid_freq_value == 0. ? 0. : freq_37 / __gen_06_last_valid_freq_value);

                    if (ratio_38 > 1.7 && ratio_38 < 2.3) {
                        freq_37 = freq_37 / (number)2;
                    } else if (ratio_38 > 0.85 && ratio_38 < 1.15) {
                        if (__gen_06_prev_conf_value > 0.7 && confidence_12_59 < 0.6) {
                            freq_37 = freq_37 / (number)2;
                        }
                    }
                }
            } else if (confidence_12_59 > 0.7) {
                __gen_06_low_conf_count_value = 0;
                __gen_06_last_valid_freq_value = freq_37;
            }
        }

        __gen_06_freq_buffer3_value = __gen_06_freq_buffer2_value;
        __gen_06_freq_buffer2_value = __gen_06_freq_buffer1_value;
        __gen_06_freq_buffer1_value = freq_37;
        number a_13_60 = __gen_06_freq_buffer1_value;
        number b_14_61 = __gen_06_freq_buffer2_value;
        number c_15_62 = __gen_06_freq_buffer3_value;

        if (a_13_60 > b_14_61) {
            temp_40 = a_13_60;
            a_13_60 = b_14_61;
            b_14_61 = temp_40;
        }

        if (b_14_61 > c_15_62) {
            temp_40 = b_14_61;
            b_14_61 = c_15_62;
            c_15_62 = temp_40;
        }

        if (a_13_60 > b_14_61) {
            temp_40 = a_13_60;
            a_13_60 = b_14_61;
            b_14_61 = temp_40;
        }

        number median_freq_16_63 = b_14_61;
        number adapt_smooth_17_64 = 0.7;

        if (confidence_12_59 > 0.8) {
            adapt_smooth_17_64 = 0.7 * 0.5;
        }

        if (median_freq_16_63 > 0) {
            smoothed_freq_39 = median_freq_16_63 * (1 - adapt_smooth_17_64) + __gen_06_prev_freq_value * adapt_smooth_17_64;
        } else {
            smoothed_freq_39 = __gen_06_prev_freq_value * 0.95;
        }

        number smoothed_conf_18_65 = confidence_12_59 * (1 - 0.7 * 0.5) + __gen_06_prev_conf_value * 0.7 * 0.5;
        number gate_on_thresh_19_66 = 0.3;
        number gate_off_thresh_20_67 = 0.3 - 0.15;

        if (__gen_06_gate_state_value == 0) {
            if (smoothed_conf_18_65 > gate_on_thresh_19_66) {
                __gen_06_gate_state_value = 1;
                __gen_06_hold_counter_value = 10;
            }
        } else {
            if (smoothed_conf_18_65 > gate_off_thresh_20_67) {
                __gen_06_hold_counter_value = 10;
            } else {
                __gen_06_hold_counter_value = __gen_06_hold_counter_value - 1;

                if (__gen_06_hold_counter_value <= 0) {
                    __gen_06_gate_state_value = 0;
                    __gen_06_hold_counter_value = 0;
                }
            }
        }

        if (__gen_06_gate_state_value > 0) {
            output_freq_41 = smoothed_freq_39;
        } else {
            output_freq_41 = 0;
        }

        __gen_06_prev_freq_value = smoothed_freq_39;
        __gen_06_prev_conf_value = smoothed_conf_18_65;
        number expr_21_68 = output_freq_41;
        number expr_22_69 = smoothed_conf_18_65;
        out1[(Index)i] = expr_21_68;
    }

    this->gen_06_writepos_value = __gen_06_writepos_value;
    this->gen_06_framecount_value = __gen_06_framecount_value;
    this->gen_06_prev_tau1_value = __gen_06_prev_tau1_value;
    this->gen_06_prev_tau2_value = __gen_06_prev_tau2_value;
    this->gen_06_prev_tau3_value = __gen_06_prev_tau3_value;
    this->gen_06_detected_tau_value = __gen_06_detected_tau_value;
    this->gen_06_min_value_value = __gen_06_min_value_value;
    this->gen_06_refined_tau_value = __gen_06_refined_tau_value;
    this->gen_06_low_conf_count_value = __gen_06_low_conf_count_value;
    this->gen_06_low_conf_freq_value = __gen_06_low_conf_freq_value;
    this->gen_06_last_valid_freq_value = __gen_06_last_valid_freq_value;
    this->gen_06_prev_conf_value = __gen_06_prev_conf_value;
    this->gen_06_freq_buffer3_value = __gen_06_freq_buffer3_value;
    this->gen_06_freq_buffer2_value = __gen_06_freq_buffer2_value;
    this->gen_06_freq_buffer1_value = __gen_06_freq_buffer1_value;
    this->gen_06_prev_freq_value = __gen_06_prev_freq_value;
    this->gen_06_gate_state_value = __gen_06_gate_state_value;
    this->gen_06_hold_counter_value = __gen_06_hold_counter_value;
}

void gen_05_perform(const Sample * in1, SampleValue * out1, Index n) {
    auto int_1_0 = this->intnum(25);
    auto mstosamps_2_1 = this->mstosamps(int_1_0);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number slide_3_3 = this->gen_05_slide_2_next(in1[(Index)i], mstosamps_2_1, mstosamps_2_1);
        out1[(Index)i] = slide_3_3;
    }
}

void ftom_tilde_01_perform(const Sample * frequency, SampleValue * out, Index n) {
    auto __ftom_tilde_01_base = this->ftom_tilde_01_base;

    for (Index i = 0; i < n; i++) {
        number v = this->ftom_tilde_01_innerFtoM_next(frequency[(Index)i], __ftom_tilde_01_base);
        out[(Index)i] = (v == -999.0 ? 0.0 : v);
    }
}

void dspexpr_04_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = rnbo_fround(in1[(Index)i] * 1 / (number)1) * 1;//#map:_###_obj_###_:1
    }
}

void gen_04_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number latch_1_1 = this->gen_04_latch_0_next(in1[(Index)i], in2[(Index)i]);
        out1[(Index)i] = latch_1_1;
    }
}

void p_01_in12_number_set(number v) {
    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->updateTime(this->_currentTime, (ENGINE*)nullptr);
        }
    }

    for (Index i = 0; i < 8; i++) {
        if (i + 1 == this->p_01_target || 0 == this->p_01_target) {
            this->p_01[i]->eventinlet_10_out1_number_set(v);
        }
    }
}

void expr_18_out1_set(number v) {
    this->expr_18_out1 = v;
    this->p_01_in12_number_set(this->expr_18_out1);
}

void expr_18_in1_bang() {
    this->expr_18_out1_set(this->expr_18_in1 - this->expr_18_in2);//#map:-_obj-46:1
}

void eventoutlet_01_in1_bang_bang() {
    this->getEngine()->sendBangMessage(TAG("out3"), TAG(""), this->_currentTime);;
}

void route_01_nomatch_bang_bang() {
    this->expr_18_in1_bang();
    this->eventoutlet_01_in1_bang_bang();
}

void route_01_match1_bang_bang() {}

void route_01_match1_number_set(number ) {}

template<typename LISTTYPE> void route_01_match1_list_set(const LISTTYPE& ) {}

void expr_18_in1_set(number in1) {
    this->expr_18_in1 = in1;
    this->expr_18_out1_set(this->expr_18_in1 - this->expr_18_in2);//#map:-_obj-46:1
}

void eventoutlet_01_in1_number_set(number v) {
    this->getEngine()->sendNumMessage(TAG("out3"), TAG(""), v, this->_currentTime);
}

void route_01_nomatch_number_set(number v) {
    this->expr_18_in1_set(v);
    this->eventoutlet_01_in1_number_set(v);
}

template<typename LISTTYPE> void eventoutlet_01_in1_list_set(const LISTTYPE& v) {
    this->getEngine()->sendListMessage(TAG("out3"), TAG(""), v, this->_currentTime);
}

void expr_18_in2_set(number v) {
    this->expr_18_in2 = v;
}

template<typename LISTTYPE> void route_01_nomatch_list_set(const LISTTYPE& v) {
    {
        if (v->length > 1)
            this->expr_18_in2_set(v[1]);

        number converted = (v->length > 0 ? v[0] : 0);
        this->expr_18_in1_set(converted);
    }

    this->eventoutlet_01_in1_list_set(v);
}

template<typename LISTTYPE> void route_01_input_list_set(const LISTTYPE& v) {
    if ((bool)(!(bool)(v->length)))
        this->route_01_nomatch_bang_bang();
    else {
        number check = v[0];
        list input = jsCreateListCopy(v);
        input->shift();
        bool nomatch = true;

        if (check == this->route_01_selector1) {
            if (input->length == 0)
                this->route_01_match1_bang_bang();
            else if (input->length == 1)
                this->route_01_match1_number_set(input[0]);
            else
                this->route_01_match1_list_set(input);

            nomatch = false;
        }

        if ((bool)(nomatch)) {
            if (v->length == 1) {
                this->route_01_nomatch_number_set(v[0]);
            } else {
                this->route_01_nomatch_list_set(v);
            }
        }
    }
}

void route_01_input_number_set(number v) {
    this->route_01_input_list_set(listbase<number, 1>{v});
}

void numbertilde_02_perform(const SampleValue * input_signal, SampleValue * output, Index n) {
    auto __numbertilde_02_currentIntervalInSamples = this->numbertilde_02_currentIntervalInSamples;
    auto __numbertilde_02_lastValue = this->numbertilde_02_lastValue;
    auto __numbertilde_02_currentInterval = this->numbertilde_02_currentInterval;
    auto __numbertilde_02_rampInSamples = this->numbertilde_02_rampInSamples;
    auto __numbertilde_02_outValue = this->numbertilde_02_outValue;
    auto __numbertilde_02_currentMode = this->numbertilde_02_currentMode;
    number monitorvalue = input_signal[0];

    for (Index i = 0; i < n; i++) {
        if (__numbertilde_02_currentMode == 0) {
            output[(Index)i] = this->numbertilde_02_smooth_next(
                __numbertilde_02_outValue,
                __numbertilde_02_rampInSamples,
                __numbertilde_02_rampInSamples
            );
        } else {
            output[(Index)i] = input_signal[(Index)i];
        }
    }

    __numbertilde_02_currentInterval -= n;

    if (monitorvalue != __numbertilde_02_lastValue && __numbertilde_02_currentInterval <= 0) {
        __numbertilde_02_currentInterval = __numbertilde_02_currentIntervalInSamples;

        this->getEngine()->scheduleClockEventWithValue(
            this,
            -1494586265,
            this->sampsToMs((SampleIndex)(this->vs)) + this->_currentTime,
            monitorvalue
        );;

        __numbertilde_02_lastValue = monitorvalue;
        ;
    }

    this->numbertilde_02_currentInterval = __numbertilde_02_currentInterval;
    this->numbertilde_02_lastValue = __numbertilde_02_lastValue;
}

void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * 0.707;//#map:_###_obj_###_:1
    }
}

void signalsend_04_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_01_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * 0.707;//#map:_###_obj_###_:1
    }
}

void signalsend_05_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_02_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void gen_03_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number slide_1_1 = this->gen_03_slide_0_next(in5, this->sr / (number)40, this->sr / (number)40);
        number mul_2_2 = slide_1_1 * 0.25;
        number cycle_3 = 0;
        number cycleindex_4 = 0;
        array<number, 2> result_5 = this->gen_03_cycle_4_next(mul_2_2, 0);
        cycleindex_4 = result_5[1];
        cycle_3 = result_5[0];
        number mul_5_6 = in2[(Index)i] * cycle_3;
        number mul_6_7 = in1[(Index)i] * cycle_3;
        number rsub_7_8 = 1 - slide_1_1;
        number mul_8_9 = rsub_7_8 * 0.25;
        number cycle_9 = 0;
        number cycleindex_10 = 0;
        array<number, 2> result_11 = this->gen_03_cycle_10_next(mul_8_9, 0);
        cycleindex_10 = result_11[1];
        cycle_9 = result_11[0];
        number mul_11_12 = in4[(Index)i] * cycle_9;
        out2[(Index)i] = mul_5_6 + mul_11_12;
        number mul_12_13 = in3[(Index)i] * cycle_9;
        out1[(Index)i] = mul_12_13 + mul_6_7;
    }
}

void recordtilde_01_perform(
    number record,
    number begin,
    number end,
    const SampleValue * input1,
    SampleValue * sync,
    Index n
) {
    RNBO_UNUSED(input1);
    RNBO_UNUSED(end);
    RNBO_UNUSED(begin);
    auto __recordtilde_01_loop = this->recordtilde_01_loop;
    auto __recordtilde_01_wIndex = this->recordtilde_01_wIndex;
    auto __recordtilde_01_lastRecord = this->recordtilde_01_lastRecord;
    auto __recordtilde_01_append = this->recordtilde_01_append;
    auto __recordtilde_01_buffer = this->recordtilde_01_buffer;
    ConstSampleArray<1> input = {input1};
    number bufferSize = __recordtilde_01_buffer->getSize();
    number srInv = (number)1 / this->sr;

    if (bufferSize > 0) {
        number maxChannel = __recordtilde_01_buffer->getChannels();
        number touched = false;

        for (Index i = 0; i < n; i++) {
            number loopBegin = 0;
            number loopEnd = bufferSize;

            if (loopEnd > loopBegin) {
                if ((bool)(__recordtilde_01_append)) {
                    if ((bool)(record) && __recordtilde_01_lastRecord != record && __recordtilde_01_wIndex >= loopEnd) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                } else {
                    if ((bool)(record) && __recordtilde_01_lastRecord != record) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                }

                if (record != 0 && __recordtilde_01_wIndex < loopEnd) {
                    for (number channel = 0; channel < 1; channel++) {
                        number effectiveChannel = channel + 0;

                        if (effectiveChannel < maxChannel) {
                            __recordtilde_01_buffer->setSample(channel, __recordtilde_01_wIndex, input[(Index)channel][(Index)i]);
                            touched = true;
                        } else
                            break;
                    }

                    __recordtilde_01_wIndex++;

                    if ((bool)(__recordtilde_01_loop) && __recordtilde_01_wIndex >= loopEnd) {
                        __recordtilde_01_wIndex = loopBegin;
                    }
                } else {
                    sync[(Index)i] = 0;
                }

                if ((bool)(!(bool)(__recordtilde_01_append)))
                    __recordtilde_01_lastRecord = record;
            }
        }

        if ((bool)(touched)) {
            __recordtilde_01_buffer->setTouched(true);
            __recordtilde_01_buffer->setSampleRate(this->sr);
        }
    }

    this->recordtilde_01_lastRecord = __recordtilde_01_lastRecord;
    this->recordtilde_01_wIndex = __recordtilde_01_wIndex;
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void data_02_srout_set(number ) {}

void data_02_chanout_set(number ) {}

void data_02_sizeout_set(number v) {
    this->data_02_sizeout = v;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

number p_01_calcActiveVoices() {
    {
        number activeVoices = 0;

        for (Index i = 0; i < 8; i++) {
            if ((bool)(!(bool)(this->p_01[(Index)i]->getIsMuted())))
                activeVoices++;
        }

        return activeVoices;
    }
}

void message_03_init() {
    this->message_03_set_set(listbase<number, 1>{0.5});
}

number gen_02_switch_getvalue() {
    return this->gen_02_switch_value;
}

void gen_02_switch_setvalue(number val) {
    this->gen_02_switch_value = val;
}

void gen_02_switch_reset() {
    this->gen_02_switch_value = 0;
}

void gen_02_switch_init() {
    this->gen_02_switch_value = 0;
}

number numbertilde_01_smooth_d_next(number x) {
    number temp = (number)(x - this->numbertilde_01_smooth_d_prev);
    this->numbertilde_01_smooth_d_prev = x;
    return temp;
}

void numbertilde_01_smooth_d_dspsetup() {
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_smooth_d_reset() {
    this->numbertilde_01_smooth_d_prev = 0;
}

number numbertilde_01_smooth_next(number x, number up, number down) {
    if (this->numbertilde_01_smooth_d_next(x) != 0.) {
        if (x > this->numbertilde_01_smooth_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->numbertilde_01_smooth_index = _up;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _up;
        } else if (x < this->numbertilde_01_smooth_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->numbertilde_01_smooth_index = _down;
            this->numbertilde_01_smooth_increment = (x - this->numbertilde_01_smooth_prev) / _down;
        }
    }

    if (this->numbertilde_01_smooth_index > 0) {
        this->numbertilde_01_smooth_prev += this->numbertilde_01_smooth_increment;
        this->numbertilde_01_smooth_index -= 1;
    } else {
        this->numbertilde_01_smooth_prev = x;
    }

    return this->numbertilde_01_smooth_prev;
}

void numbertilde_01_smooth_reset() {
    this->numbertilde_01_smooth_prev = 0;
    this->numbertilde_01_smooth_index = 0;
    this->numbertilde_01_smooth_increment = 0;
    this->numbertilde_01_smooth_d_reset();
}

void numbertilde_01_init() {
    this->numbertilde_01_currentMode = 1;
}

void numbertilde_01_dspsetup(bool force) {
    if ((bool)(this->numbertilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->numbertilde_01_currentIntervalInSamples = this->mstosamps(100);
    this->numbertilde_01_currentInterval = this->numbertilde_01_currentIntervalInSamples;
    this->numbertilde_01_rampInSamples = this->mstosamps(this->numbertilde_01_ramp);
    this->numbertilde_01_setupDone = true;
    this->numbertilde_01_smooth_d_dspsetup();
}

void data_02_init() {
    this->data_02_buffer->setWantsFill(true);
}

Index data_02_evaluateSizeExpr(number samplerate, number vectorsize) {
    RNBO_UNUSED(vectorsize);
    RNBO_UNUSED(samplerate);
    number size = 0;
    return (Index)(size);
}

void data_02_dspsetup(bool force) {
    if ((bool)(this->data_02_setupDone) && (bool)(!(bool)(force)))
        return;

    if (this->data_02_sizemode == 2) {
        this->data_02_buffer = this->data_02_buffer->setSize((Index)(this->mstosamps(this->data_02_sizems)));
        updateDataRef(this, this->data_02_buffer);
    } else if (this->data_02_sizemode == 3) {
        this->data_02_buffer = this->data_02_buffer->setSize(this->data_02_evaluateSizeExpr(this->sr, this->vs));
        updateDataRef(this, this->data_02_buffer);
    }

    this->data_02_setupDone = true;
}

void data_02_bufferUpdated() {
    this->data_02_report();
}

void data_02_report() {
    this->data_02_srout_set(this->data_02_buffer->getSampleRate());
    this->data_02_chanout_set(this->data_02_buffer->getChannels());
    this->data_02_sizeout_set(this->data_02_buffer->getSize());
}

number gen_03_slide_0_next(number x, number up, number down) {
    number temp = x - this->gen_03_slide_0_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_03_slide_0_prev = this->gen_03_slide_0_prev + ((x > this->gen_03_slide_0_prev ? iup : idown)) * temp;
    return this->gen_03_slide_0_prev;
}

void gen_03_slide_0_reset() {
    this->gen_03_slide_0_prev = 0;
}

number gen_03_cycle_4_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_03_cycle_4_ph_conv;

    if (this->gen_03_cycle_4_ph_currentPhase < 0.)
        this->gen_03_cycle_4_ph_currentPhase = 1. + this->gen_03_cycle_4_ph_currentPhase;

    if (this->gen_03_cycle_4_ph_currentPhase > 1.)
        this->gen_03_cycle_4_ph_currentPhase = this->gen_03_cycle_4_ph_currentPhase - 1.;

    number tmp = this->gen_03_cycle_4_ph_currentPhase;
    this->gen_03_cycle_4_ph_currentPhase += pincr;
    return tmp;
}

void gen_03_cycle_4_ph_reset() {
    this->gen_03_cycle_4_ph_currentPhase = 0;
}

void gen_03_cycle_4_ph_dspsetup() {
    this->gen_03_cycle_4_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_03_cycle_4_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_03_cycle_4_buffer[(Index)idx];
        number y1 = this->gen_03_cycle_4_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_03_cycle_4_dspsetup() {
    this->gen_03_cycle_4_phasei = 0;
    this->gen_03_cycle_4_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_03_cycle_4_wrap = (Int)(this->gen_03_cycle_4_buffer->getSize()) - 1;
}

void gen_03_cycle_4_reset() {
    this->gen_03_cycle_4_phasei = 0;
}

void gen_03_cycle_4_bufferUpdated() {
    this->gen_03_cycle_4_wrap = (Int)(this->gen_03_cycle_4_buffer->getSize()) - 1;
}

number gen_03_cycle_10_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);

    {
        {}
    }

    number pincr = freq * this->gen_03_cycle_10_ph_conv;

    if (this->gen_03_cycle_10_ph_currentPhase < 0.)
        this->gen_03_cycle_10_ph_currentPhase = 1. + this->gen_03_cycle_10_ph_currentPhase;

    if (this->gen_03_cycle_10_ph_currentPhase > 1.)
        this->gen_03_cycle_10_ph_currentPhase = this->gen_03_cycle_10_ph_currentPhase - 1.;

    number tmp = this->gen_03_cycle_10_ph_currentPhase;
    this->gen_03_cycle_10_ph_currentPhase += pincr;
    return tmp;
}

void gen_03_cycle_10_ph_reset() {
    this->gen_03_cycle_10_ph_currentPhase = 0;
}

void gen_03_cycle_10_ph_dspsetup() {
    this->gen_03_cycle_10_ph_conv = (this->sr == 0. ? 0. : (number)1 / this->sr);
}

array<number, 2> gen_03_cycle_10_next(number frequency, number phase_offset) {
    RNBO_UNUSED(phase_offset);

    {
        UInt32 uint_phase;

        {
            uint_phase = uint32_trunc(frequency * 4294967296.0);
        }

        UInt32 idx = (UInt32)(uint32_rshift(uint_phase, 18));
        number frac = ((BinOpInt)((BinOpInt)uint_phase & (BinOpInt)262143)) * 3.81471181759574e-6;
        number y0 = this->gen_03_cycle_10_buffer[(Index)idx];
        number y1 = this->gen_03_cycle_10_buffer[(Index)((BinOpInt)(idx + 1) & (BinOpInt)16383)];
        number y = y0 + frac * (y1 - y0);
        return {y, uint_phase * 0.232830643653869629e-9};
    }
}

void gen_03_cycle_10_dspsetup() {
    this->gen_03_cycle_10_phasei = 0;
    this->gen_03_cycle_10_f2i = (this->sr == 0. ? 0. : (number)4294967296 / this->sr);
    this->gen_03_cycle_10_wrap = (Int)(this->gen_03_cycle_10_buffer->getSize()) - 1;
}

void gen_03_cycle_10_reset() {
    this->gen_03_cycle_10_phasei = 0;
}

void gen_03_cycle_10_bufferUpdated() {
    this->gen_03_cycle_10_wrap = (Int)(this->gen_03_cycle_10_buffer->getSize()) - 1;
}

void gen_03_dspsetup(bool force) {
    if ((bool)(this->gen_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_03_setupDone = true;
    this->gen_03_cycle_4_ph_dspsetup();
    this->gen_03_cycle_4_dspsetup();
    this->gen_03_cycle_10_ph_dspsetup();
    this->gen_03_cycle_10_dspsetup();
}

number gen_04_latch_0_next(number x, number control) {
    if (control != 0.) {
        this->gen_04_latch_0_value = x;
    }

    return this->gen_04_latch_0_value;
}

void gen_04_latch_0_dspsetup() {
    this->gen_04_latch_0_reset();
}

void gen_04_latch_0_init() {
    this->gen_04_latch_0_reset();
}

void gen_04_latch_0_reset() {
    this->gen_04_latch_0_value = 0;
}

void gen_04_dspsetup(bool force) {
    if ((bool)(this->gen_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->gen_04_setupDone = true;
    this->gen_04_latch_0_dspsetup();
}

number ftom_tilde_01_innerFtoM_next(number frequency, number tuning) {
    if (frequency <= 0.0) {
        return -999;
    }

    if (frequency == this->ftom_tilde_01_innerFtoM_lastInValue && tuning == this->ftom_tilde_01_innerFtoM_lastTuning) {
        return this->ftom_tilde_01_innerFtoM_lastOutValue;
    }

    this->ftom_tilde_01_innerFtoM_lastInValue = frequency;
    this->ftom_tilde_01_innerFtoM_lastTuning = tuning;
    this->ftom_tilde_01_innerFtoM_lastOutValue = (frequency == 0 || tuning == 0 ? 0 : 69. + 17.31234050465299 * rnbo_log(frequency / tuning));

    {
        this->ftom_tilde_01_innerFtoM_lastOutValue = rnbo_fround(this->ftom_tilde_01_innerFtoM_lastOutValue * 1 / (number)1) * 1;
    }

    return this->ftom_tilde_01_innerFtoM_lastOutValue;
}

void ftom_tilde_01_innerFtoM_reset() {
    this->ftom_tilde_01_innerFtoM_lastInValue = 0;
    this->ftom_tilde_01_innerFtoM_lastOutValue = 0;
    this->ftom_tilde_01_innerFtoM_lastTuning = 0;
}

void ftom_tilde_01_innerScala_mid(Int v) {
    this->ftom_tilde_01_innerScala_kbmMid = v;
    this->ftom_tilde_01_innerScala_updateRefFreq();
}

void ftom_tilde_01_innerScala_ref(Int v) {
    this->ftom_tilde_01_innerScala_kbmRefNum = v;
    this->ftom_tilde_01_innerScala_updateRefFreq();
}

void ftom_tilde_01_innerScala_base(number v) {
    this->ftom_tilde_01_innerScala_kbmRefFreq = v;
    this->ftom_tilde_01_innerScala_updateRefFreq();
}

void ftom_tilde_01_innerScala_init() {
    list sclValid = {
        12,
        100,
        0,
        200,
        0,
        300,
        0,
        400,
        0,
        500,
        0,
        600,
        0,
        700,
        0,
        800,
        0,
        900,
        0,
        1000,
        0,
        1100,
        0,
        2,
        1
    };

    this->ftom_tilde_01_innerScala_updateScale(sclValid);
}

template<typename LISTTYPE = list> void ftom_tilde_01_innerScala_update(const LISTTYPE& scale, const LISTTYPE& map) {
    if (scale->length > 0) {
        this->ftom_tilde_01_innerScala_updateScale(scale);
    }

    if (map->length > 0) {
        this->ftom_tilde_01_innerScala_updateMap(map);
    }
}

number ftom_tilde_01_innerScala_mtof(number note) {
    if ((bool)(this->ftom_tilde_01_innerScala_lastValid) && this->ftom_tilde_01_innerScala_lastNote == note) {
        return this->ftom_tilde_01_innerScala_lastFreq;
    }

    array<Int, 2> degoct = this->ftom_tilde_01_innerScala_applyKBM(note);
    number out = 0;

    if (degoct[1] > 0) {
        out = this->ftom_tilde_01_innerScala_applySCL(degoct[0], fract(note), this->ftom_tilde_01_innerScala_refFreq);
    }

    this->ftom_tilde_01_innerScala_updateLast(note, out);
    return out;
}

number ftom_tilde_01_innerScala_ftom(number hz) {
    if (hz <= 0.0) {
        return 0.0;
    }

    if ((bool)(this->ftom_tilde_01_innerScala_lastValid) && this->ftom_tilde_01_innerScala_lastFreq == hz) {
        return this->ftom_tilde_01_innerScala_lastNote;
    }

    array<number, 2> df = this->ftom_tilde_01_innerScala_hztodeg(hz);
    Int degree = (Int)(df[0]);
    number frac = df[1];
    number out = 0;

    if (this->ftom_tilde_01_innerScala_kbmSize == 0) {
        out = this->ftom_tilde_01_innerScala_kbmMid + degree;
    } else {
        array<Int, 2> octdeg = this->ftom_tilde_01_innerScala_octdegree(degree, this->ftom_tilde_01_innerScala_kbmOctaveDegree);
        number oct = (number)(octdeg[0]);
        Int index = (Int)(octdeg[1]);
        Index entry = 0;

        for (Index i = 0; i < this->ftom_tilde_01_innerScala_kbmMapSize; i++) {
            if (index == this->ftom_tilde_01_innerScala_kbmValid[(Index)(i + this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET)]) {
                entry = i;
                break;
            }
        }

        out = oct * this->ftom_tilde_01_innerScala_kbmSize + entry + this->ftom_tilde_01_innerScala_kbmMid;
    }

    out = out + frac;
    this->ftom_tilde_01_innerScala_updateLast(out, hz);
    return this->ftom_tilde_01_innerScala_lastNote;
}

template<typename LISTTYPE = list> Int ftom_tilde_01_innerScala_updateScale(const LISTTYPE& scl) {
    if (scl->length < 1) {
        return 0;
    }

    number sclDataEntries = scl[0] * 2 + 1;

    if (sclDataEntries <= scl->length) {
        this->ftom_tilde_01_innerScala_lastValid = false;
        this->ftom_tilde_01_innerScala_sclExpMul = {};
        number last = 1;

        for (Index i = 1; i < sclDataEntries; i += 2) {
            const number c = (const number)(scl[(Index)(i + 0)]);
            const number d = (const number)(scl[(Index)(i + 1)]);

            if (d <= 0) {
                last = c / (number)1200;
            } else {
                last = rnbo_log2(c / d);
            }

            this->ftom_tilde_01_innerScala_sclExpMul->push(last);
        }

        this->ftom_tilde_01_innerScala_sclOctaveMul = last;
        this->ftom_tilde_01_innerScala_sclEntryCount = (Int)(this->ftom_tilde_01_innerScala_sclExpMul->length);

        if (scl->length >= sclDataEntries + 3) {
            this->ftom_tilde_01_innerScala_kbmMid = (Int)(scl[(Index)(sclDataEntries + 2)]);
            this->ftom_tilde_01_innerScala_kbmRefNum = (Int)(scl[(Index)(sclDataEntries + 1)]);
            this->ftom_tilde_01_innerScala_kbmRefFreq = scl[(Index)(sclDataEntries + 0)];
            this->ftom_tilde_01_innerScala_kbmSize = (Int)(0);
        }

        this->ftom_tilde_01_innerScala_updateRefFreq();
        return 1;
    }

    return 0;
}

template<typename LISTTYPE = list> Int ftom_tilde_01_innerScala_updateMap(const LISTTYPE& kbm) {
    list _kbm = kbm;

    if (_kbm->length == 1 && _kbm[0] == 0.0) {
        _kbm = {0.0, 0.0, 0.0, 60.0, 69.0, 440.0};
    }

    if (_kbm->length >= 6 && _kbm[0] >= 0.0) {
        this->ftom_tilde_01_innerScala_lastValid = false;
        Index size = (Index)(_kbm[0]);
        Int octave = 12;

        if (_kbm->length > 6) {
            octave = (Int)(_kbm[6]);
        }

        if (size > 0 && _kbm->length < this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET) {
            return 0;
        }

        this->ftom_tilde_01_innerScala_kbmSize = (Int)(size);
        this->ftom_tilde_01_innerScala_kbmMin = (Int)(_kbm[1]);
        this->ftom_tilde_01_innerScala_kbmMax = (Int)(_kbm[2]);
        this->ftom_tilde_01_innerScala_kbmMid = (Int)(_kbm[3]);
        this->ftom_tilde_01_innerScala_kbmRefNum = (Int)(_kbm[4]);
        this->ftom_tilde_01_innerScala_kbmRefFreq = _kbm[5];
        this->ftom_tilde_01_innerScala_kbmOctaveDegree = octave;
        this->ftom_tilde_01_innerScala_kbmValid = _kbm;
        this->ftom_tilde_01_innerScala_kbmMapSize = (_kbm->length - this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET > _kbm->length ? _kbm->length : (_kbm->length - this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET < 0 ? 0 : _kbm->length - this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET));
        this->ftom_tilde_01_innerScala_updateRefFreq();
        return 1;
    }

    return 0;
}

void ftom_tilde_01_innerScala_updateLast(number note, number freq) {
    this->ftom_tilde_01_innerScala_lastValid = true;
    this->ftom_tilde_01_innerScala_lastNote = note;
    this->ftom_tilde_01_innerScala_lastFreq = freq;
}

array<number, 2> ftom_tilde_01_innerScala_hztodeg(number hz) {
    number hza = rnbo_abs(hz);

    number octave = rnbo_floor(
        rnbo_log2(hza / this->ftom_tilde_01_innerScala_refFreq) / this->ftom_tilde_01_innerScala_sclOctaveMul
    );

    Int i = 0;
    number frac = 0;
    number n = 0;

    for (; i < this->ftom_tilde_01_innerScala_sclEntryCount; i++) {
        number c = this->ftom_tilde_01_innerScala_applySCLOctIndex(octave, i + 0, 0.0, this->ftom_tilde_01_innerScala_refFreq);
        n = this->ftom_tilde_01_innerScala_applySCLOctIndex(octave, i + 1, 0.0, this->ftom_tilde_01_innerScala_refFreq);

        if (c <= hza && hza < n) {
            if (c != hza) {
                frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
            }

            break;
        }
    }

    if (i == this->ftom_tilde_01_innerScala_sclEntryCount && n != hza) {
        number c = n;
        n = this->ftom_tilde_01_innerScala_applySCLOctIndex(octave + 1, 0, 0.0, this->ftom_tilde_01_innerScala_refFreq);
        frac = rnbo_log2(hza / c) / rnbo_log2(n / c);
    }

    number deg = i + octave * this->ftom_tilde_01_innerScala_sclEntryCount;

    {
        deg = rnbo_fround((deg + frac) * 1 / (number)1) * 1;
        frac = 0.0;
    }

    return {deg, frac};
}

array<Int, 2> ftom_tilde_01_innerScala_octdegree(Int degree, Int count) {
    Int octave = 0;
    Int index = 0;

    if (degree < 0) {
        octave = -(1 + (-1 - degree) / count);
        index = -degree % count;

        if (index > 0) {
            index = count - index;
        }
    } else {
        octave = degree / count;
        index = degree % count;
    }

    return {octave, index};
}

array<Int, 2> ftom_tilde_01_innerScala_applyKBM(number note) {
    if ((this->ftom_tilde_01_innerScala_kbmMin == this->ftom_tilde_01_innerScala_kbmMax && this->ftom_tilde_01_innerScala_kbmMax == 0) || (note >= this->ftom_tilde_01_innerScala_kbmMin && note <= this->ftom_tilde_01_innerScala_kbmMax)) {
        Int degree = (Int)(rnbo_floor(note - this->ftom_tilde_01_innerScala_kbmMid));

        if (this->ftom_tilde_01_innerScala_kbmSize == 0) {
            return {degree, 1};
        }

        array<Int, 2> octdeg = this->ftom_tilde_01_innerScala_octdegree(degree, this->ftom_tilde_01_innerScala_kbmSize);
        Int octave = (Int)(octdeg[0]);
        Index index = (Index)(octdeg[1]);

        if (this->ftom_tilde_01_innerScala_kbmMapSize > index) {
            degree = (Int)(this->ftom_tilde_01_innerScala_kbmValid[(Index)(this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET + index)]);

            if (degree >= 0) {
                return {degree + octave * this->ftom_tilde_01_innerScala_kbmOctaveDegree, 1};
            }
        }
    }

    return {-1, 0};
}

number ftom_tilde_01_innerScala_applySCL(Int degree, number frac, number refFreq) {
    array<Int, 2> octdeg = this->ftom_tilde_01_innerScala_octdegree(degree, this->ftom_tilde_01_innerScala_sclEntryCount);
    return this->ftom_tilde_01_innerScala_applySCLOctIndex(octdeg[0], octdeg[1], frac, refFreq);
}

number ftom_tilde_01_innerScala_applySCLOctIndex(number octave, Int index, number frac, number refFreq) {
    number p = 0;

    if (index > 0) {
        p = this->ftom_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
    }

    if (frac > 0) {
        p = this->linearinterp(frac, p, this->ftom_tilde_01_innerScala_sclExpMul[(Index)index]);
    } else if (frac < 0) {
        p = this->linearinterp(-frac, this->ftom_tilde_01_innerScala_sclExpMul[(Index)index], p);
    }

    return refFreq * rnbo_pow(2, p + octave * this->ftom_tilde_01_innerScala_sclOctaveMul);
}

void ftom_tilde_01_innerScala_updateRefFreq() {
    this->ftom_tilde_01_innerScala_lastValid = false;
    Int refOffset = (Int)(this->ftom_tilde_01_innerScala_kbmRefNum - this->ftom_tilde_01_innerScala_kbmMid);

    if (refOffset == 0) {
        this->ftom_tilde_01_innerScala_refFreq = this->ftom_tilde_01_innerScala_kbmRefFreq;
    } else {
        Int base = (Int)(this->ftom_tilde_01_innerScala_kbmSize);

        if (base < 1) {
            base = this->ftom_tilde_01_innerScala_sclEntryCount;
        }

        array<Int, 2> octdeg = this->ftom_tilde_01_innerScala_octdegree(refOffset, base);
        number oct = (number)(octdeg[0]);
        Int index = (Int)(octdeg[1]);

        if (base > 0) {
            oct = oct + rnbo_floor(index / base);
            index = index % base;
        }

        if (index >= 0 && index < this->ftom_tilde_01_innerScala_kbmSize) {
            if (index < (Int)(this->ftom_tilde_01_innerScala_kbmMapSize)) {
                index = (Int)(this->ftom_tilde_01_innerScala_kbmValid[(Index)((Index)(index) + this->ftom_tilde_01_innerScala_KBM_MAP_OFFSET)]);
            } else {
                index = -1;
            }
        }

        if (index < 0 || index > (Int)(this->ftom_tilde_01_innerScala_sclExpMul->length))
            {} else {
            number p = 0;

            if (index > 0) {
                p = this->ftom_tilde_01_innerScala_sclExpMul[(Index)(index - 1)];
            }

            this->ftom_tilde_01_innerScala_refFreq = this->ftom_tilde_01_innerScala_kbmRefFreq / rnbo_pow(2, p + oct * this->ftom_tilde_01_innerScala_sclOctaveMul);
        }
    }
}

void ftom_tilde_01_innerScala_reset() {
    this->ftom_tilde_01_innerScala_lastValid = false;
    this->ftom_tilde_01_innerScala_lastNote = 0;
    this->ftom_tilde_01_innerScala_lastFreq = 0;
    this->ftom_tilde_01_innerScala_sclEntryCount = 0;
    this->ftom_tilde_01_innerScala_sclOctaveMul = 1;
    this->ftom_tilde_01_innerScala_sclExpMul = {};
    this->ftom_tilde_01_innerScala_kbmValid = {0, 0, 0, 60, 69, 440};
    this->ftom_tilde_01_innerScala_kbmMid = 60;
    this->ftom_tilde_01_innerScala_kbmRefNum = 69;
    this->ftom_tilde_01_innerScala_kbmRefFreq = 440;
    this->ftom_tilde_01_innerScala_kbmSize = 0;
    this->ftom_tilde_01_innerScala_kbmMin = 0;
    this->ftom_tilde_01_innerScala_kbmMax = 0;
    this->ftom_tilde_01_innerScala_kbmOctaveDegree = 12;
    this->ftom_tilde_01_innerScala_kbmMapSize = 0;
    this->ftom_tilde_01_innerScala_refFreq = 261.63;
}

void ftom_tilde_01_init() {
    this->ftom_tilde_01_innerScala_update(this->ftom_tilde_01_scale, this->ftom_tilde_01_map);
}

number gen_05_slide_2_next(number x, number up, number down) {
    number temp = x - this->gen_05_slide_2_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_05_slide_2_prev = this->gen_05_slide_2_prev + ((x > this->gen_05_slide_2_prev ? iup : idown)) * temp;
    return this->gen_05_slide_2_prev;
}

void gen_05_slide_2_reset() {
    this->gen_05_slide_2_prev = 0;
}

number numbertilde_02_smooth_d_next(number x) {
    number temp = (number)(x - this->numbertilde_02_smooth_d_prev);
    this->numbertilde_02_smooth_d_prev = x;
    return temp;
}

void numbertilde_02_smooth_d_dspsetup() {
    this->numbertilde_02_smooth_d_reset();
}

void numbertilde_02_smooth_d_reset() {
    this->numbertilde_02_smooth_d_prev = 0;
}

number numbertilde_02_smooth_next(number x, number up, number down) {
    if (this->numbertilde_02_smooth_d_next(x) != 0.) {
        if (x > this->numbertilde_02_smooth_prev) {
            number _up = up;

            if (_up < 1)
                _up = 1;

            this->numbertilde_02_smooth_index = _up;
            this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _up;
        } else if (x < this->numbertilde_02_smooth_prev) {
            number _down = down;

            if (_down < 1)
                _down = 1;

            this->numbertilde_02_smooth_index = _down;
            this->numbertilde_02_smooth_increment = (x - this->numbertilde_02_smooth_prev) / _down;
        }
    }

    if (this->numbertilde_02_smooth_index > 0) {
        this->numbertilde_02_smooth_prev += this->numbertilde_02_smooth_increment;
        this->numbertilde_02_smooth_index -= 1;
    } else {
        this->numbertilde_02_smooth_prev = x;
    }

    return this->numbertilde_02_smooth_prev;
}

void numbertilde_02_smooth_reset() {
    this->numbertilde_02_smooth_prev = 0;
    this->numbertilde_02_smooth_index = 0;
    this->numbertilde_02_smooth_increment = 0;
    this->numbertilde_02_smooth_d_reset();
}

void numbertilde_02_init() {
    this->numbertilde_02_currentMode = 1;
}

void numbertilde_02_dspsetup(bool force) {
    if ((bool)(this->numbertilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->numbertilde_02_currentIntervalInSamples = this->mstosamps(100);
    this->numbertilde_02_currentInterval = this->numbertilde_02_currentIntervalInSamples;
    this->numbertilde_02_rampInSamples = this->mstosamps(this->numbertilde_02_ramp);
    this->numbertilde_02_setupDone = true;
    this->numbertilde_02_smooth_d_dspsetup();
}

number gen_06_writepos_getvalue() {
    return this->gen_06_writepos_value;
}

void gen_06_writepos_setvalue(number val) {
    this->gen_06_writepos_value = val;
}

void gen_06_writepos_reset() {
    this->gen_06_writepos_value = 0;
}

void gen_06_writepos_init() {
    this->gen_06_writepos_value = 0;
}

number gen_06_framecount_getvalue() {
    return this->gen_06_framecount_value;
}

void gen_06_framecount_setvalue(number val) {
    this->gen_06_framecount_value = val;
}

void gen_06_framecount_reset() {
    this->gen_06_framecount_value = 0;
}

void gen_06_framecount_init() {
    this->gen_06_framecount_value = 0;
}

number gen_06_detected_tau_getvalue() {
    return this->gen_06_detected_tau_value;
}

void gen_06_detected_tau_setvalue(number val) {
    this->gen_06_detected_tau_value = val;
}

void gen_06_detected_tau_reset() {
    this->gen_06_detected_tau_value = 0;
}

void gen_06_detected_tau_init() {
    this->gen_06_detected_tau_value = 0;
}

number gen_06_min_value_getvalue() {
    return this->gen_06_min_value_value;
}

void gen_06_min_value_setvalue(number val) {
    this->gen_06_min_value_value = val;
}

void gen_06_min_value_reset() {
    this->gen_06_min_value_value = 0;
}

void gen_06_min_value_init() {
    this->gen_06_min_value_value = 1;
}

number gen_06_prev_tau1_getvalue() {
    return this->gen_06_prev_tau1_value;
}

void gen_06_prev_tau1_setvalue(number val) {
    this->gen_06_prev_tau1_value = val;
}

void gen_06_prev_tau1_reset() {
    this->gen_06_prev_tau1_value = 0;
}

void gen_06_prev_tau1_init() {
    this->gen_06_prev_tau1_value = 0;
}

number gen_06_prev_tau2_getvalue() {
    return this->gen_06_prev_tau2_value;
}

void gen_06_prev_tau2_setvalue(number val) {
    this->gen_06_prev_tau2_value = val;
}

void gen_06_prev_tau2_reset() {
    this->gen_06_prev_tau2_value = 0;
}

void gen_06_prev_tau2_init() {
    this->gen_06_prev_tau2_value = 0;
}

number gen_06_prev_tau3_getvalue() {
    return this->gen_06_prev_tau3_value;
}

void gen_06_prev_tau3_setvalue(number val) {
    this->gen_06_prev_tau3_value = val;
}

void gen_06_prev_tau3_reset() {
    this->gen_06_prev_tau3_value = 0;
}

void gen_06_prev_tau3_init() {
    this->gen_06_prev_tau3_value = 0;
}

number gen_06_refined_tau_getvalue() {
    return this->gen_06_refined_tau_value;
}

void gen_06_refined_tau_setvalue(number val) {
    this->gen_06_refined_tau_value = val;
}

void gen_06_refined_tau_reset() {
    this->gen_06_refined_tau_value = 0;
}

void gen_06_refined_tau_init() {
    this->gen_06_refined_tau_value = 0;
}

number gen_06_prev_freq_getvalue() {
    return this->gen_06_prev_freq_value;
}

void gen_06_prev_freq_setvalue(number val) {
    this->gen_06_prev_freq_value = val;
}

void gen_06_prev_freq_reset() {
    this->gen_06_prev_freq_value = 0;
}

void gen_06_prev_freq_init() {
    this->gen_06_prev_freq_value = 0;
}

number gen_06_prev_conf_getvalue() {
    return this->gen_06_prev_conf_value;
}

void gen_06_prev_conf_setvalue(number val) {
    this->gen_06_prev_conf_value = val;
}

void gen_06_prev_conf_reset() {
    this->gen_06_prev_conf_value = 0;
}

void gen_06_prev_conf_init() {
    this->gen_06_prev_conf_value = 0;
}

number gen_06_freq_buffer1_getvalue() {
    return this->gen_06_freq_buffer1_value;
}

void gen_06_freq_buffer1_setvalue(number val) {
    this->gen_06_freq_buffer1_value = val;
}

void gen_06_freq_buffer1_reset() {
    this->gen_06_freq_buffer1_value = 0;
}

void gen_06_freq_buffer1_init() {
    this->gen_06_freq_buffer1_value = 0;
}

number gen_06_freq_buffer2_getvalue() {
    return this->gen_06_freq_buffer2_value;
}

void gen_06_freq_buffer2_setvalue(number val) {
    this->gen_06_freq_buffer2_value = val;
}

void gen_06_freq_buffer2_reset() {
    this->gen_06_freq_buffer2_value = 0;
}

void gen_06_freq_buffer2_init() {
    this->gen_06_freq_buffer2_value = 0;
}

number gen_06_freq_buffer3_getvalue() {
    return this->gen_06_freq_buffer3_value;
}

void gen_06_freq_buffer3_setvalue(number val) {
    this->gen_06_freq_buffer3_value = val;
}

void gen_06_freq_buffer3_reset() {
    this->gen_06_freq_buffer3_value = 0;
}

void gen_06_freq_buffer3_init() {
    this->gen_06_freq_buffer3_value = 0;
}

number gen_06_last_valid_freq_getvalue() {
    return this->gen_06_last_valid_freq_value;
}

void gen_06_last_valid_freq_setvalue(number val) {
    this->gen_06_last_valid_freq_value = val;
}

void gen_06_last_valid_freq_reset() {
    this->gen_06_last_valid_freq_value = 0;
}

void gen_06_last_valid_freq_init() {
    this->gen_06_last_valid_freq_value = 0;
}

number gen_06_hold_counter_getvalue() {
    return this->gen_06_hold_counter_value;
}

void gen_06_hold_counter_setvalue(number val) {
    this->gen_06_hold_counter_value = val;
}

void gen_06_hold_counter_reset() {
    this->gen_06_hold_counter_value = 0;
}

void gen_06_hold_counter_init() {
    this->gen_06_hold_counter_value = 0;
}

number gen_06_gate_state_getvalue() {
    return this->gen_06_gate_state_value;
}

void gen_06_gate_state_setvalue(number val) {
    this->gen_06_gate_state_value = val;
}

void gen_06_gate_state_reset() {
    this->gen_06_gate_state_value = 0;
}

void gen_06_gate_state_init() {
    this->gen_06_gate_state_value = 0;
}

number gen_06_low_conf_freq_getvalue() {
    return this->gen_06_low_conf_freq_value;
}

void gen_06_low_conf_freq_setvalue(number val) {
    this->gen_06_low_conf_freq_value = val;
}

void gen_06_low_conf_freq_reset() {
    this->gen_06_low_conf_freq_value = 0;
}

void gen_06_low_conf_freq_init() {
    this->gen_06_low_conf_freq_value = 0;
}

number gen_06_low_conf_count_getvalue() {
    return this->gen_06_low_conf_count_value;
}

void gen_06_low_conf_count_setvalue(number val) {
    this->gen_06_low_conf_count_value = val;
}

void gen_06_low_conf_count_reset() {
    this->gen_06_low_conf_count_value = 0;
}

void gen_06_low_conf_count_init() {
    this->gen_06_low_conf_count_value = 0;
}

void midinotecontroller_01_init() {
    for (Index i = 0; i < 16; i++) {
        this->midinotecontroller_01_channel_pitchbend[(Index)i] = 0x2000;
    }

    for (Index i = 0; i < 8; i++) {
        this->midinotecontroller_01_voice_lastontime[(Index)i] = -1;
    }
}

void midinotecontroller_01_sendnoteoff(Int target) {
    Int i = (Int)(target - 1);

    if (this->midinotecontroller_01_voice_state[(Index)i] != MIDI_NoteState_Off) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(target);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_NoteOffMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)i])
        );

        this->midinotecontroller_01_midiout_set(this->midinotecontroller_01_voice_notenumber[(Index)i]);
        this->midinotecontroller_01_midiout_set(64);
        this->midinotecontroller_01_voice_state[(Index)i] = MIDI_NoteState_Off;
        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpitchbend(Int v) {
    if (v >= 0 && v < 8) {
        number currentTarget = this->midinotecontroller_01_currenttarget;
        this->midinotecontroller_01_target_set(v + 1);
        Int totalbendamount = (Int)(this->midinotecontroller_01_channel_pitchbend[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]);

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)MIDI_PitchBendMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
        );

        this->midinotecontroller_01_midiout_set((BinOpInt)((BinOpInt)totalbendamount & (BinOpInt)0x7F));

        this->midinotecontroller_01_midiout_set(
            (BinOpInt)((BinOpInt)((BinOpInt)totalbendamount >> imod_nocast((UBinOpInt)imod_nocast((UBinOpInt)7, 32), 32)) & (BinOpInt)0x7F)
        );

        this->midinotecontroller_01_target_set(currentTarget);
    }
}

void midinotecontroller_01_sendpressure(Int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_ChannelPressureMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(
        this->midinotecontroller_01_channel_pressure[(Index)this->midinotecontroller_01_voice_channel[(Index)v]]
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendtimbre(Int v) {
    number currentTarget = this->midinotecontroller_01_currenttarget;
    this->midinotecontroller_01_target_set(v + 1);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreLSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)MIDI_CCMask | (BinOpInt)this->midinotecontroller_01_voice_channel[(Index)v])
    );

    this->midinotecontroller_01_midiout_set(MIDI_CC_TimbreMSB);

    this->midinotecontroller_01_midiout_set(
        (BinOpInt)((BinOpInt)((BinOpInt)this->midinotecontroller_01_channel_timbre[(Index)this->midinotecontroller_01_voice_channel[(Index)v]] >> imod_nocast((UBinOpInt)7, 32)) & (BinOpInt)0x7F)
    );

    this->midinotecontroller_01_target_set(currentTarget);
}

void midinotecontroller_01_sendallnotesoff() {
    for (Int i = 1; i <= 8; i++) {
        this->midinotecontroller_01_sendnoteoff(i);
    }
}

void globaltransport_advance() {}

void globaltransport_dspsetup(bool ) {}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    expr_04_in1 = 0;
    expr_04_in2 = 0.01;
    expr_04_out1 = 0;
    param_01_value = 0;
    param_02_value = 160;
    param_03_value = 15;
    expr_08_in1 = 0;
    expr_08_in2 = 4;
    expr_08_out1 = 0;
    expr_09_in1 = 0;
    expr_09_in2 = 0.01;
    expr_09_out1 = 0;
    param_04_value = 50;
    param_05_value = 50;
    param_06_value = 260;
    expr_13_in1 = 0;
    expr_13_in2 = 0.01;
    expr_13_out1 = 0;
    expr_14_in1 = 0;
    expr_14_in2 = 0.01;
    expr_14_out1 = 0;
    param_07_value = 100;
    param_08_value = 200;
    param_09_value = 200;
    p_01_target = 0;
    p_01_midiin = 0;
    gen_02_in1 = 0;
    numbertilde_01_input_number = 0;
    numbertilde_01_ramp = 0;
    recordtilde_01_append = 1;
    recordtilde_01_record = 0;
    recordtilde_01_begin = 0;
    recordtilde_01_end = -1;
    recordtilde_01_loop = 1;
    midiin_02_port = 0;
    data_02_sizeout = 0;
    data_02_size = 0;
    data_02_sizems = 1000;
    data_02_normalize = 0.995;
    data_02_channels = 1;
    gen_03_in1 = 0;
    gen_03_in2 = 0;
    gen_03_in3 = 0;
    gen_03_in4 = 0;
    gen_03_in5 = 0;
    dspexpr_03_in1 = 0;
    dspexpr_03_in2 = 0.707;
    expr_18_in1 = 0;
    expr_18_in2 = 60;
    expr_18_out1 = 0;
    gen_04_in1 = 0;
    gen_04_in2 = 0;
    ftom_tilde_01_frequency = 0;
    ftom_tilde_01_base = 440;
    gen_05_in1 = 0;
    numbertilde_02_input_number = 0;
    numbertilde_02_ramp = 0;
    dspexpr_04_in1 = 0;
    dspexpr_04_in2 = 1;
    gen_06_in1 = 0;
    gen_06_minfreq = 65;
    gen_06_maxfreq = 2000;
    gen_06_window_size = 1024;
    gen_06_threshold = 0.1;
    gen_06_smooth_factor = 0.7;
    gen_06_confidence_threshold = 0.3;
    gen_06_hold_time = 10;
    gen_06_hysteresis = 0.15;
    gen_06_octave_correct = 1;
    gen_06_process_rate = 256;
    dspexpr_05_in1 = 0;
    dspexpr_05_in2 = 0.707;
    route_01_selector1 = -1;
    ctlin_01_input = 0;
    ctlin_01_controller = 0;
    ctlin_01_channel = -1;
    expr_05_in1 = 0;
    expr_05_in2 = 0.007874015748;
    expr_05_out1 = 0;
    ctlin_02_input = 0;
    ctlin_02_controller = 0;
    ctlin_02_channel = -1;
    expr_06_in1 = 0;
    expr_06_in2 = 0.007874015748;
    expr_06_out1 = 0;
    ctlin_03_input = 0;
    ctlin_03_controller = 0;
    ctlin_03_channel = -1;
    expr_07_in1 = 0;
    expr_07_in2 = 0.007874015748;
    expr_07_out1 = 0;
    ctlin_04_input = 0;
    ctlin_04_controller = 0;
    ctlin_04_channel = -1;
    expr_10_in1 = 0;
    expr_10_in2 = 0.007874015748;
    expr_10_out1 = 0;
    ctlin_05_input = 0;
    ctlin_05_controller = 0;
    ctlin_05_channel = -1;
    expr_11_in1 = 0;
    expr_11_in2 = 0.007874015748;
    expr_11_out1 = 0;
    ctlin_06_input = 0;
    ctlin_06_controller = 0;
    ctlin_06_channel = -1;
    expr_12_in1 = 0;
    expr_12_in2 = 0.007874015748;
    expr_12_out1 = 0;
    ctlin_07_input = 0;
    ctlin_07_controller = 0;
    ctlin_07_channel = -1;
    expr_15_in1 = 0;
    expr_15_in2 = 0.007874015748;
    expr_15_out1 = 0;
    ctlin_08_input = 0;
    ctlin_08_controller = 0;
    ctlin_08_channel = -1;
    expr_16_in1 = 0;
    expr_16_in2 = 0.007874015748;
    expr_16_out1 = 0;
    ctlin_09_input = 0;
    ctlin_09_controller = 0;
    ctlin_09_channel = -1;
    expr_17_in1 = 0;
    expr_17_in2 = 0.007874015748;
    expr_17_out1 = 0;
    midinotecontroller_01_currenttarget = 0;
    midinotecontroller_01_midiin = 0;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    p_01_currentStatus = -1;
    p_01_mididata[0] = 0;
    p_01_mididata[1] = 0;
    p_01_mididata[2] = 0;
    gen_02_switch_value = 0;
    numbertilde_01_currentInterval = 0;
    numbertilde_01_currentIntervalInSamples = 0;
    numbertilde_01_lastValue = 0;
    numbertilde_01_outValue = 0;
    numbertilde_01_rampInSamples = 0;
    numbertilde_01_currentMode = 0;
    numbertilde_01_smooth_d_prev = 0;
    numbertilde_01_smooth_prev = 0;
    numbertilde_01_smooth_index = 0;
    numbertilde_01_smooth_increment = 0;
    numbertilde_01_setupDone = false;
    recordtilde_01_wIndex = 0;
    recordtilde_01_lastRecord = 0;
    data_02_sizemode = 2;
    data_02_setupDone = false;
    gen_03_slide_0_prev = 0;
    gen_03_cycle_4_ph_currentPhase = 0;
    gen_03_cycle_4_ph_conv = 0;
    gen_03_cycle_4_wrap = 0;
    gen_03_cycle_10_ph_currentPhase = 0;
    gen_03_cycle_10_ph_conv = 0;
    gen_03_cycle_10_wrap = 0;
    gen_03_setupDone = false;
    gen_04_latch_0_value = 0;
    gen_04_setupDone = false;
    ftom_tilde_01_innerFtoM_lastInValue = 0;
    ftom_tilde_01_innerFtoM_lastOutValue = 0;
    ftom_tilde_01_innerFtoM_lastTuning = 0;
    ftom_tilde_01_innerScala_lastValid = false;
    ftom_tilde_01_innerScala_lastNote = 0;
    ftom_tilde_01_innerScala_lastFreq = 0;
    ftom_tilde_01_innerScala_sclEntryCount = 0;
    ftom_tilde_01_innerScala_sclOctaveMul = 1;
    ftom_tilde_01_innerScala_kbmValid = { 0, 0, 0, 60, 69, 440 };
    ftom_tilde_01_innerScala_kbmMid = 60;
    ftom_tilde_01_innerScala_kbmRefNum = 69;
    ftom_tilde_01_innerScala_kbmRefFreq = 440;
    ftom_tilde_01_innerScala_kbmSize = 0;
    ftom_tilde_01_innerScala_kbmMin = 0;
    ftom_tilde_01_innerScala_kbmMax = 0;
    ftom_tilde_01_innerScala_kbmOctaveDegree = 12;
    ftom_tilde_01_innerScala_kbmMapSize = 0;
    ftom_tilde_01_innerScala_refFreq = 261.63;
    gen_05_slide_2_prev = 0;
    numbertilde_02_currentInterval = 0;
    numbertilde_02_currentIntervalInSamples = 0;
    numbertilde_02_lastValue = 0;
    numbertilde_02_outValue = 0;
    numbertilde_02_rampInSamples = 0;
    numbertilde_02_currentMode = 0;
    numbertilde_02_smooth_d_prev = 0;
    numbertilde_02_smooth_prev = 0;
    numbertilde_02_smooth_index = 0;
    numbertilde_02_smooth_increment = 0;
    numbertilde_02_setupDone = false;
    gen_06_writepos_value = 0;
    gen_06_framecount_value = 0;
    gen_06_detected_tau_value = 0;
    gen_06_min_value_value = 0;
    gen_06_prev_tau1_value = 0;
    gen_06_prev_tau2_value = 0;
    gen_06_prev_tau3_value = 0;
    gen_06_refined_tau_value = 0;
    gen_06_prev_freq_value = 0;
    gen_06_prev_conf_value = 0;
    gen_06_freq_buffer1_value = 0;
    gen_06_freq_buffer2_value = 0;
    gen_06_freq_buffer3_value = 0;
    gen_06_last_valid_freq_value = 0;
    gen_06_hold_counter_value = 0;
    gen_06_gate_state_value = 0;
    gen_06_low_conf_freq_value = 0;
    gen_06_low_conf_count_value = 0;
    ctlin_01_status = 0;
    ctlin_01_byte1 = -1;
    ctlin_01_inchan = 0;
    ctlin_02_status = 0;
    ctlin_02_byte1 = -1;
    ctlin_02_inchan = 0;
    ctlin_03_status = 0;
    ctlin_03_byte1 = -1;
    ctlin_03_inchan = 0;
    ctlin_04_status = 0;
    ctlin_04_byte1 = -1;
    ctlin_04_inchan = 0;
    ctlin_05_status = 0;
    ctlin_05_byte1 = -1;
    ctlin_05_inchan = 0;
    ctlin_06_status = 0;
    ctlin_06_byte1 = -1;
    ctlin_06_inchan = 0;
    ctlin_07_status = 0;
    ctlin_07_byte1 = -1;
    ctlin_07_inchan = 0;
    ctlin_08_status = 0;
    ctlin_08_byte1 = -1;
    ctlin_08_inchan = 0;
    ctlin_09_status = 0;
    ctlin_09_byte1 = -1;
    ctlin_09_inchan = 0;
    midinotecontroller_01_currentStatus = -1;
    midinotecontroller_01_status = -1;
    midinotecontroller_01_byte1 = -1;
    midinotecontroller_01_zone_masterchannel = 1;
    midinotecontroller_01_zone_numnotechannels = 15;
    midinotecontroller_01_zone_masterpitchbendrange = 2;
    midinotecontroller_01_zone_pernotepitchbendrange = 48;
    midinotecontroller_01_muteval = { 0, 0 };
    globaltransport_tempo = nullptr;
    globaltransport_state = nullptr;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

    // data ref strings
    struct DataRefStrings {
    	static constexpr auto& name0 = "sample";
    	static constexpr auto& file0 = "";
    	static constexpr auto& tag0 = "buffer~";
    	static constexpr auto& name1 = "RNBODefaultSinus";
    	static constexpr auto& file1 = "";
    	static constexpr auto& tag1 = "buffer~";
    	static constexpr auto& name2 = "norm_buffer";
    	static constexpr auto& file2 = "";
    	static constexpr auto& tag2 = "buffer~";
    	static constexpr auto& name3 = "diff_buffer";
    	static constexpr auto& file3 = "";
    	static constexpr auto& tag3 = "buffer~";
    	static constexpr auto& name4 = "yin_buffer";
    	static constexpr auto& file4 = "";
    	static constexpr auto& tag4 = "buffer~";
    	DataRefStrings* operator->() { return this; }
    	const DataRefStrings* operator->() const { return this; }
    };

    DataRefStrings dataRefStrings;

// member variables

    number expr_04_in1;
    number expr_04_in2;
    number expr_04_out1;
    number param_01_value;
    number param_02_value;
    number param_03_value;
    number expr_08_in1;
    number expr_08_in2;
    number expr_08_out1;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    number param_04_value;
    number param_05_value;
    number param_06_value;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number p_01_target;
    number p_01_midiin;
    list message_03_set;
    number gen_02_in1;
    number numbertilde_01_input_number;
    number numbertilde_01_ramp;
    number recordtilde_01_append;
    number recordtilde_01_record;
    number recordtilde_01_begin;
    number recordtilde_01_end;
    number recordtilde_01_loop;
    number midiin_02_port;
    number data_02_sizeout;
    number data_02_size;
    number data_02_sizems;
    number data_02_normalize;
    number data_02_channels;
    number gen_03_in1;
    number gen_03_in2;
    number gen_03_in3;
    number gen_03_in4;
    number gen_03_in5;
    number dspexpr_03_in1;
    number dspexpr_03_in2;
    number expr_18_in1;
    number expr_18_in2;
    number expr_18_out1;
    number gen_04_in1;
    number gen_04_in2;
    number ftom_tilde_01_frequency;
    list ftom_tilde_01_scale;
    list ftom_tilde_01_map;
    number ftom_tilde_01_base;
    number gen_05_in1;
    number numbertilde_02_input_number;
    number numbertilde_02_ramp;
    number dspexpr_04_in1;
    number dspexpr_04_in2;
    number gen_06_in1;
    number gen_06_minfreq;
    number gen_06_maxfreq;
    number gen_06_window_size;
    number gen_06_threshold;
    number gen_06_smooth_factor;
    number gen_06_confidence_threshold;
    number gen_06_hold_time;
    number gen_06_hysteresis;
    number gen_06_octave_correct;
    number gen_06_process_rate;
    number dspexpr_05_in1;
    number dspexpr_05_in2;
    number route_01_selector1;
    number ctlin_01_input;
    number ctlin_01_controller;
    number ctlin_01_channel;
    number expr_05_in1;
    number expr_05_in2;
    number expr_05_out1;
    number ctlin_02_input;
    number ctlin_02_controller;
    number ctlin_02_channel;
    number expr_06_in1;
    number expr_06_in2;
    number expr_06_out1;
    number ctlin_03_input;
    number ctlin_03_controller;
    number ctlin_03_channel;
    number expr_07_in1;
    number expr_07_in2;
    number expr_07_out1;
    number ctlin_04_input;
    number ctlin_04_controller;
    number ctlin_04_channel;
    number expr_10_in1;
    number expr_10_in2;
    number expr_10_out1;
    number ctlin_05_input;
    number ctlin_05_controller;
    number ctlin_05_channel;
    number expr_11_in1;
    number expr_11_in2;
    number expr_11_out1;
    number ctlin_06_input;
    number ctlin_06_controller;
    number ctlin_06_channel;
    number expr_12_in1;
    number expr_12_in2;
    number expr_12_out1;
    number ctlin_07_input;
    number ctlin_07_controller;
    number ctlin_07_channel;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number ctlin_08_input;
    number ctlin_08_controller;
    number ctlin_08_channel;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    number ctlin_09_input;
    number ctlin_09_controller;
    number ctlin_09_channel;
    number expr_17_in1;
    number expr_17_in2;
    number expr_17_out1;
    number midinotecontroller_01_currenttarget;
    number midinotecontroller_01_midiin;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[5];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    Int p_01_currentStatus;
    uint8_t p_01_mididata[3];
    number gen_02_switch_value;
    SampleIndex numbertilde_01_currentInterval;
    SampleIndex numbertilde_01_currentIntervalInSamples;
    number numbertilde_01_lastValue;
    number numbertilde_01_outValue;
    number numbertilde_01_rampInSamples;
    Int numbertilde_01_currentMode;
    number numbertilde_01_smooth_d_prev;
    number numbertilde_01_smooth_prev;
    number numbertilde_01_smooth_index;
    number numbertilde_01_smooth_increment;
    bool numbertilde_01_setupDone;
    Float32BufferRef recordtilde_01_buffer;
    SampleIndex recordtilde_01_wIndex;
    number recordtilde_01_lastRecord;
    Float32BufferRef data_02_buffer;
    Int data_02_sizemode;
    bool data_02_setupDone;
    number gen_03_slide_0_prev;
    number gen_03_cycle_4_ph_currentPhase;
    number gen_03_cycle_4_ph_conv;
    SampleBufferRef gen_03_cycle_4_buffer;
    Int gen_03_cycle_4_wrap;
    UInt32 gen_03_cycle_4_phasei;
    SampleValue gen_03_cycle_4_f2i;
    number gen_03_cycle_10_ph_currentPhase;
    number gen_03_cycle_10_ph_conv;
    SampleBufferRef gen_03_cycle_10_buffer;
    Int gen_03_cycle_10_wrap;
    UInt32 gen_03_cycle_10_phasei;
    SampleValue gen_03_cycle_10_f2i;
    bool gen_03_setupDone;
    number gen_04_latch_0_value;
    bool gen_04_setupDone;
    number ftom_tilde_01_innerFtoM_lastInValue;
    number ftom_tilde_01_innerFtoM_lastOutValue;
    number ftom_tilde_01_innerFtoM_lastTuning;
    const Index ftom_tilde_01_innerScala_KBM_MAP_OFFSET = 7;
    bool ftom_tilde_01_innerScala_lastValid;
    number ftom_tilde_01_innerScala_lastNote;
    number ftom_tilde_01_innerScala_lastFreq;
    Int ftom_tilde_01_innerScala_sclEntryCount;
    number ftom_tilde_01_innerScala_sclOctaveMul;
    list ftom_tilde_01_innerScala_sclExpMul;
    list ftom_tilde_01_innerScala_kbmValid;
    Int ftom_tilde_01_innerScala_kbmMid;
    Int ftom_tilde_01_innerScala_kbmRefNum;
    number ftom_tilde_01_innerScala_kbmRefFreq;
    Int ftom_tilde_01_innerScala_kbmSize;
    Int ftom_tilde_01_innerScala_kbmMin;
    Int ftom_tilde_01_innerScala_kbmMax;
    Int ftom_tilde_01_innerScala_kbmOctaveDegree;
    Index ftom_tilde_01_innerScala_kbmMapSize;
    number ftom_tilde_01_innerScala_refFreq;
    number gen_05_slide_2_prev;
    SampleIndex numbertilde_02_currentInterval;
    SampleIndex numbertilde_02_currentIntervalInSamples;
    number numbertilde_02_lastValue;
    number numbertilde_02_outValue;
    number numbertilde_02_rampInSamples;
    Int numbertilde_02_currentMode;
    number numbertilde_02_smooth_d_prev;
    number numbertilde_02_smooth_prev;
    number numbertilde_02_smooth_index;
    number numbertilde_02_smooth_increment;
    bool numbertilde_02_setupDone;
    SampleBufferRef gen_06_norm_buffer;
    SampleBufferRef gen_06_diff_buffer;
    SampleBufferRef gen_06_yin_buffer;
    number gen_06_writepos_value;
    number gen_06_framecount_value;
    number gen_06_detected_tau_value;
    number gen_06_min_value_value;
    number gen_06_prev_tau1_value;
    number gen_06_prev_tau2_value;
    number gen_06_prev_tau3_value;
    number gen_06_refined_tau_value;
    number gen_06_prev_freq_value;
    number gen_06_prev_conf_value;
    number gen_06_freq_buffer1_value;
    number gen_06_freq_buffer2_value;
    number gen_06_freq_buffer3_value;
    number gen_06_last_valid_freq_value;
    number gen_06_hold_counter_value;
    number gen_06_gate_state_value;
    number gen_06_low_conf_freq_value;
    number gen_06_low_conf_count_value;
    Int ctlin_01_status;
    Int ctlin_01_byte1;
    Int ctlin_01_inchan;
    Int ctlin_02_status;
    Int ctlin_02_byte1;
    Int ctlin_02_inchan;
    Int ctlin_03_status;
    Int ctlin_03_byte1;
    Int ctlin_03_inchan;
    Int ctlin_04_status;
    Int ctlin_04_byte1;
    Int ctlin_04_inchan;
    Int ctlin_05_status;
    Int ctlin_05_byte1;
    Int ctlin_05_inchan;
    Int ctlin_06_status;
    Int ctlin_06_byte1;
    Int ctlin_06_inchan;
    Int ctlin_07_status;
    Int ctlin_07_byte1;
    Int ctlin_07_inchan;
    Int ctlin_08_status;
    Int ctlin_08_byte1;
    Int ctlin_08_inchan;
    Int ctlin_09_status;
    Int ctlin_09_byte1;
    Int ctlin_09_inchan;
    Int midinotecontroller_01_currentStatus;
    Int midinotecontroller_01_status;
    Int midinotecontroller_01_byte1;
    Int midinotecontroller_01_zone_masterchannel;
    Int midinotecontroller_01_zone_numnotechannels;
    Int midinotecontroller_01_zone_masterpitchbendrange;
    Int midinotecontroller_01_zone_pernotepitchbendrange;
    number midinotecontroller_01_channel_pitchbend[16] = { };
    number midinotecontroller_01_channel_pressure[16] = { };
    number midinotecontroller_01_channel_timbre[16] = { };
    Int midinotecontroller_01_channel_sustain[16] = { };
    MillisecondTime midinotecontroller_01_voice_lastontime[8] = { };
    number midinotecontroller_01_voice_notenumber[8] = { };
    number midinotecontroller_01_voice_channel[8] = { };
    number midinotecontroller_01_voice_state[8] = { };
    number midinotecontroller_01_notesdown[129] = { };
    number midinotecontroller_01_note_lastvelocity[128] = { };
    list midinotecontroller_01_muteval;
    signal globaltransport_tempo;
    signal globaltransport_state;
    number stackprotect_count;
    DataRef sample;
    DataRef RNBODefaultSinus;
    DataRef norm_buffer;
    DataRef diff_buffer;
    DataRef yin_buffer;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_05 p_01[8];
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

