/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef GCI_AVRO_HH_1781829477__H_
#define GCI_AVRO_HH_1781829477__H_


#include <sstream>
#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"
#include "avro/ValidSchema.hh"
#include "avro/Compiler.hh"
#include "avro/DataFile.hh"

namespace c {
    struct channels {
        std::vector<int32_t > PositionV13;
        std::vector<int32_t > PositionW13;
        std::vector<int32_t > PositionV24;
        std::vector<int32_t > PositionW24;
        std::vector<int32_t > PositionV57;
        std::vector<int32_t > PositionW57;
        std::vector<int32_t > Positionz1;
        std::vector<int32_t > PositionZ12;
        std::vector<int32_t > CommandeV1;
        std::vector<int32_t > CommandeV3;
        std::vector<int32_t > CommandeV2;
        std::vector<int32_t > CommandeV4;
        std::vector<int32_t > CommandeV5;
        std::vector<int32_t > CommandeV7;
        std::vector<int32_t > CommandeW1;
        std::vector<int32_t > CommandeW3;
        std::vector<int32_t > CommandeW2;
        std::vector<int32_t > CommandeW4;
        std::vector<int32_t > CommandeW5;
        std::vector<int32_t > CommandeW7;
        std::vector<int32_t > Commandez1;
        std::vector<int32_t > CommandeZ2;
        std::vector<int32_t > TDCBit;
        std::vector<int32_t > CurrentV1;
        std::vector<int32_t > CurrentV3;
        std::vector<int32_t > CurrentV2;
        std::vector<int32_t > CurrentV4;
        std::vector<int32_t > CurrentV5;
        std::vector<int32_t > CurrentV7;
        std::vector<int32_t > CurrentW1;
        std::vector<int32_t > CurrentW3;
        std::vector<int32_t > CurrentW2;
        std::vector<int32_t > CurrentW4;
        std::vector<int32_t > CurrentW5;
        std::vector<int32_t > CurrentW7;
        std::vector<int32_t > CurrentZ1;
        std::vector<int32_t > CurrentZ2;
        std::vector<int32_t > CurrentZ3;
        std::vector<int32_t > CurrentZ4;
        std::vector<int32_t > Rotation_Frequency_A;
        std::vector<int32_t > Rotation_Frequency_B;
        std::vector<int32_t > SPV_speed_A;
        std::vector<int32_t > SPV_speed_B;
        std::vector<int32_t > UnbalanceA13;
        std::vector<int32_t > UnbalanceB13;
        std::vector<int32_t > UnbalanceA24;
        std::vector<int32_t > UnbalanceB24;
        std::vector<int32_t > UnbalanceA57;
        std::vector<int32_t > UnbalanceB57;
        std::vector<int32_t > AxialHarmonic1A;
        std::vector<int32_t > AxialHarmonic1B;
        std::vector<int32_t > MachineTemp_1_A;
        std::vector<int32_t > MachineTemp_2_A;
        std::vector<int32_t > MachineTemp_3_A;
        std::vector<int32_t > MachineTemp_4_A;
        std::vector<int32_t > MachineTemp_5_A;
        std::vector<int32_t > MachineTemp_6_A;
        std::vector<int32_t > MachineTemp_7_A;
        std::vector<int32_t > MachineTemp_8_A;
        std::vector<int32_t > MachineTemp_1_B;
        std::vector<int32_t > MachineTemp_2_B;
        std::vector<int32_t > MachineTemp_3_B;
        std::vector<int32_t > MachineTemp_4_B;
        std::vector<int32_t > MachineTemp_5_B;
        std::vector<int32_t > MachineTemp_6_B;
        std::vector<int32_t > MachineTemp_7_B;
        std::vector<int32_t > MachineTemp_8_B;
        std::vector<int32_t > coilTempV1;
        std::vector<int32_t > coilTempV3;
        std::vector<int32_t > coilTempv2;
        std::vector<int32_t > coilTempv4;
        std::vector<int32_t > coilTempv5;
        std::vector<int32_t > coilTempV7;
        std::vector<int32_t > coilTempw1;
        std::vector<int32_t > coilTempW3;
        std::vector<int32_t > coilTempW2;
        std::vector<int32_t > coilTempW4;
        std::vector<int32_t > coilTempW5;
        std::vector<int32_t > coilTempW7;
        std::vector<int32_t > coilTempZI;
        std::vector<int32_t > coilTempZ2;
        std::vector<int32_t > coilTempz3;
        std::vector<int32_t > coilTempZ4;
        std::vector<int32_t > peakPositionv13;
        std::vector<int32_t > peakPositionW13;
        std::vector<int32_t > peakPositionV24;
        std::vector<int32_t > peakPositionW24;
        std::vector<int32_t > peakPositionV57;
        std::vector<int32_t > peakPositionW57;
        std::vector<int32_t > peakPositionz1;
        std::vector<int32_t > peakPosition22;
        std::vector<int32_t > PeakElongation_Rotor_SPV;
        std::vector<int32_t > VDCMains;
        std::vector<int32_t > VDCPA_V13;
        std::vector<int32_t > VDCPA_W13;
        std::vector<int32_t > VDCPA_V24;
        std::vector<int32_t > VDCPA_W24;
        std::vector<int32_t > VDCPA_V57;
        std::vector<int32_t > VDCPA_W57;
        std::vector<int32_t > VDCPA_Z12;
        std::vector<int32_t > VDCPA_234;
        std::vector<int32_t > AmplifierTempv13;
        std::vector<int32_t > AmplifierTempW13;
        std::vector<int32_t > AmplifierTempv24;
        std::vector<int32_t > AmplifierTempW24;
        std::vector<int32_t > AmplifierTempV57;
        std::vector<int32_t > AmplifierTempW57;
        std::vector<int32_t > AmplifierTempz12;
        std::vector<int32_t > AmplifierTempz34;
        std::vector<int32_t > ISO_Bear_A;
        std::vector<int32_t > ISO_Det_A;
        std::vector<int32_t > ISO_Bear_B;
        std::vector<int32_t > ISO_Det_B;
        std::vector<int32_t > RadialHarmonicN2A13;
        std::vector<int32_t > RadialHarmonicN2B13;
        std::vector<int32_t > RadialHarmonicN2A24;
        std::vector<int32_t > RadialHarmonicN2824;
        std::vector<int32_t > RadialHarmonicN2A57;
        std::vector<int32_t > RadialHarmonicN2B57;
        std::vector<int32_t > AxialHarmonicN2A;
        std::vector<int32_t > AxialHarmonicN2B;
        channels() :
                PositionV13(std::vector<int32_t >()),
                PositionW13(std::vector<int32_t >()),
                PositionV24(std::vector<int32_t >()),
                PositionW24(std::vector<int32_t >()),
                PositionV57(std::vector<int32_t >()),
                PositionW57(std::vector<int32_t >()),
                Positionz1(std::vector<int32_t >()),
                PositionZ12(std::vector<int32_t >()),
                CommandeV1(std::vector<int32_t >()),
                CommandeV3(std::vector<int32_t >()),
                CommandeV2(std::vector<int32_t >()),
                CommandeV4(std::vector<int32_t >()),
                CommandeV5(std::vector<int32_t >()),
                CommandeV7(std::vector<int32_t >()),
                CommandeW1(std::vector<int32_t >()),
                CommandeW3(std::vector<int32_t >()),
                CommandeW2(std::vector<int32_t >()),
                CommandeW4(std::vector<int32_t >()),
                CommandeW5(std::vector<int32_t >()),
                CommandeW7(std::vector<int32_t >()),
                Commandez1(std::vector<int32_t >()),
                CommandeZ2(std::vector<int32_t >()),
                TDCBit(std::vector<int32_t >()),
                CurrentV1(std::vector<int32_t >()),
                CurrentV3(std::vector<int32_t >()),
                CurrentV2(std::vector<int32_t >()),
                CurrentV4(std::vector<int32_t >()),
                CurrentV5(std::vector<int32_t >()),
                CurrentV7(std::vector<int32_t >()),
                CurrentW1(std::vector<int32_t >()),
                CurrentW3(std::vector<int32_t >()),
                CurrentW2(std::vector<int32_t >()),
                CurrentW4(std::vector<int32_t >()),
                CurrentW5(std::vector<int32_t >()),
                CurrentW7(std::vector<int32_t >()),
                CurrentZ1(std::vector<int32_t >()),
                CurrentZ2(std::vector<int32_t >()),
                CurrentZ3(std::vector<int32_t >()),
                CurrentZ4(std::vector<int32_t >()),
                Rotation_Frequency_A(std::vector<int32_t >()),
                Rotation_Frequency_B(std::vector<int32_t >()),
                SPV_speed_A(std::vector<int32_t >()),
                SPV_speed_B(std::vector<int32_t >()),
                UnbalanceA13(std::vector<int32_t >()),
                UnbalanceB13(std::vector<int32_t >()),
                UnbalanceA24(std::vector<int32_t >()),
                UnbalanceB24(std::vector<int32_t >()),
                UnbalanceA57(std::vector<int32_t >()),
                UnbalanceB57(std::vector<int32_t >()),
                AxialHarmonic1A(std::vector<int32_t >()),
                AxialHarmonic1B(std::vector<int32_t >()),
                MachineTemp_1_A(std::vector<int32_t >()),
                MachineTemp_2_A(std::vector<int32_t >()),
                MachineTemp_3_A(std::vector<int32_t >()),
                MachineTemp_4_A(std::vector<int32_t >()),
                MachineTemp_5_A(std::vector<int32_t >()),
                MachineTemp_6_A(std::vector<int32_t >()),
                MachineTemp_7_A(std::vector<int32_t >()),
                MachineTemp_8_A(std::vector<int32_t >()),
                MachineTemp_1_B(std::vector<int32_t >()),
                MachineTemp_2_B(std::vector<int32_t >()),
                MachineTemp_3_B(std::vector<int32_t >()),
                MachineTemp_4_B(std::vector<int32_t >()),
                MachineTemp_5_B(std::vector<int32_t >()),
                MachineTemp_6_B(std::vector<int32_t >()),
                MachineTemp_7_B(std::vector<int32_t >()),
                MachineTemp_8_B(std::vector<int32_t >()),
                coilTempV1(std::vector<int32_t >()),
                coilTempV3(std::vector<int32_t >()),
                coilTempv2(std::vector<int32_t >()),
                coilTempv4(std::vector<int32_t >()),
                coilTempv5(std::vector<int32_t >()),
                coilTempV7(std::vector<int32_t >()),
                coilTempw1(std::vector<int32_t >()),
                coilTempW3(std::vector<int32_t >()),
                coilTempW2(std::vector<int32_t >()),
                coilTempW4(std::vector<int32_t >()),
                coilTempW5(std::vector<int32_t >()),
                coilTempW7(std::vector<int32_t >()),
                coilTempZI(std::vector<int32_t >()),
                coilTempZ2(std::vector<int32_t >()),
                coilTempz3(std::vector<int32_t >()),
                coilTempZ4(std::vector<int32_t >()),
                peakPositionv13(std::vector<int32_t >()),
                peakPositionW13(std::vector<int32_t >()),
                peakPositionV24(std::vector<int32_t >()),
                peakPositionW24(std::vector<int32_t >()),
                peakPositionV57(std::vector<int32_t >()),
                peakPositionW57(std::vector<int32_t >()),
                peakPositionz1(std::vector<int32_t >()),
                peakPosition22(std::vector<int32_t >()),
                PeakElongation_Rotor_SPV(std::vector<int32_t >()),
                VDCMains(std::vector<int32_t >()),
                VDCPA_V13(std::vector<int32_t >()),
                VDCPA_W13(std::vector<int32_t >()),
                VDCPA_V24(std::vector<int32_t >()),
                VDCPA_W24(std::vector<int32_t >()),
                VDCPA_V57(std::vector<int32_t >()),
                VDCPA_W57(std::vector<int32_t >()),
                VDCPA_Z12(std::vector<int32_t >()),
                VDCPA_234(std::vector<int32_t >()),
                AmplifierTempv13(std::vector<int32_t >()),
                AmplifierTempW13(std::vector<int32_t >()),
                AmplifierTempv24(std::vector<int32_t >()),
                AmplifierTempW24(std::vector<int32_t >()),
                AmplifierTempV57(std::vector<int32_t >()),
                AmplifierTempW57(std::vector<int32_t >()),
                AmplifierTempz12(std::vector<int32_t >()),
                AmplifierTempz34(std::vector<int32_t >()),
                ISO_Bear_A(std::vector<int32_t >()),
                ISO_Det_A(std::vector<int32_t >()),
                ISO_Bear_B(std::vector<int32_t >()),
                ISO_Det_B(std::vector<int32_t >()),
                RadialHarmonicN2A13(std::vector<int32_t >()),
                RadialHarmonicN2B13(std::vector<int32_t >()),
                RadialHarmonicN2A24(std::vector<int32_t >()),
                RadialHarmonicN2824(std::vector<int32_t >()),
                RadialHarmonicN2A57(std::vector<int32_t >()),
                RadialHarmonicN2B57(std::vector<int32_t >()),
                AxialHarmonicN2A(std::vector<int32_t >()),
                AxialHarmonicN2B(std::vector<int32_t >())
        { }
    };

}
namespace avro {
    template<> struct codec_traits<c::channels> {
        static void encode(Encoder& e, const c::channels& v) {
            avro::encode(e, v.PositionV13);
            avro::encode(e, v.PositionW13);
            avro::encode(e, v.PositionV24);
            avro::encode(e, v.PositionW24);
            avro::encode(e, v.PositionV57);
            avro::encode(e, v.PositionW57);
            avro::encode(e, v.Positionz1);
            avro::encode(e, v.PositionZ12);
            avro::encode(e, v.CommandeV1);
            avro::encode(e, v.CommandeV3);
            avro::encode(e, v.CommandeV2);
            avro::encode(e, v.CommandeV4);
            avro::encode(e, v.CommandeV5);
            avro::encode(e, v.CommandeV7);
            avro::encode(e, v.CommandeW1);
            avro::encode(e, v.CommandeW3);
            avro::encode(e, v.CommandeW2);
            avro::encode(e, v.CommandeW4);
            avro::encode(e, v.CommandeW5);
            avro::encode(e, v.CommandeW7);
            avro::encode(e, v.Commandez1);
            avro::encode(e, v.CommandeZ2);
            avro::encode(e, v.TDCBit);
            avro::encode(e, v.CurrentV1);
            avro::encode(e, v.CurrentV3);
            avro::encode(e, v.CurrentV2);
            avro::encode(e, v.CurrentV4);
            avro::encode(e, v.CurrentV5);
            avro::encode(e, v.CurrentV7);
            avro::encode(e, v.CurrentW1);
            avro::encode(e, v.CurrentW3);
            avro::encode(e, v.CurrentW2);
            avro::encode(e, v.CurrentW4);
            avro::encode(e, v.CurrentW5);
            avro::encode(e, v.CurrentW7);
            avro::encode(e, v.CurrentZ1);
            avro::encode(e, v.CurrentZ2);
            avro::encode(e, v.CurrentZ3);
            avro::encode(e, v.CurrentZ4);
            avro::encode(e, v.Rotation_Frequency_A);
            avro::encode(e, v.Rotation_Frequency_B);
            avro::encode(e, v.SPV_speed_A);
            avro::encode(e, v.SPV_speed_B);
            avro::encode(e, v.UnbalanceA13);
            avro::encode(e, v.UnbalanceB13);
            avro::encode(e, v.UnbalanceA24);
            avro::encode(e, v.UnbalanceB24);
            avro::encode(e, v.UnbalanceA57);
            avro::encode(e, v.UnbalanceB57);
            avro::encode(e, v.AxialHarmonic1A);
            avro::encode(e, v.AxialHarmonic1B);
            avro::encode(e, v.MachineTemp_1_A);
            avro::encode(e, v.MachineTemp_2_A);
            avro::encode(e, v.MachineTemp_3_A);
            avro::encode(e, v.MachineTemp_4_A);
            avro::encode(e, v.MachineTemp_5_A);
            avro::encode(e, v.MachineTemp_6_A);
            avro::encode(e, v.MachineTemp_7_A);
            avro::encode(e, v.MachineTemp_8_A);
            avro::encode(e, v.MachineTemp_1_B);
            avro::encode(e, v.MachineTemp_2_B);
            avro::encode(e, v.MachineTemp_3_B);
            avro::encode(e, v.MachineTemp_4_B);
            avro::encode(e, v.MachineTemp_5_B);
            avro::encode(e, v.MachineTemp_6_B);
            avro::encode(e, v.MachineTemp_7_B);
            avro::encode(e, v.MachineTemp_8_B);
            avro::encode(e, v.coilTempV1);
            avro::encode(e, v.coilTempV3);
            avro::encode(e, v.coilTempv2);
            avro::encode(e, v.coilTempv4);
            avro::encode(e, v.coilTempv5);
            avro::encode(e, v.coilTempV7);
            avro::encode(e, v.coilTempw1);
            avro::encode(e, v.coilTempW3);
            avro::encode(e, v.coilTempW2);
            avro::encode(e, v.coilTempW4);
            avro::encode(e, v.coilTempW5);
            avro::encode(e, v.coilTempW7);
            avro::encode(e, v.coilTempZI);
            avro::encode(e, v.coilTempZ2);
            avro::encode(e, v.coilTempz3);
            avro::encode(e, v.coilTempZ4);
            avro::encode(e, v.peakPositionv13);
            avro::encode(e, v.peakPositionW13);
            avro::encode(e, v.peakPositionV24);
            avro::encode(e, v.peakPositionW24);
            avro::encode(e, v.peakPositionV57);
            avro::encode(e, v.peakPositionW57);
            avro::encode(e, v.peakPositionz1);
            avro::encode(e, v.peakPosition22);
            avro::encode(e, v.PeakElongation_Rotor_SPV);
            avro::encode(e, v.VDCMains);
            avro::encode(e, v.VDCPA_V13);
            avro::encode(e, v.VDCPA_W13);
            avro::encode(e, v.VDCPA_V24);
            avro::encode(e, v.VDCPA_W24);
            avro::encode(e, v.VDCPA_V57);
            avro::encode(e, v.VDCPA_W57);
            avro::encode(e, v.VDCPA_Z12);
            avro::encode(e, v.VDCPA_234);
            avro::encode(e, v.AmplifierTempv13);
            avro::encode(e, v.AmplifierTempW13);
            avro::encode(e, v.AmplifierTempv24);
            avro::encode(e, v.AmplifierTempW24);
            avro::encode(e, v.AmplifierTempV57);
            avro::encode(e, v.AmplifierTempW57);
            avro::encode(e, v.AmplifierTempz12);
            avro::encode(e, v.AmplifierTempz34);
            avro::encode(e, v.ISO_Bear_A);
            avro::encode(e, v.ISO_Det_A);
            avro::encode(e, v.ISO_Bear_B);
            avro::encode(e, v.ISO_Det_B);
            avro::encode(e, v.RadialHarmonicN2A13);
            avro::encode(e, v.RadialHarmonicN2B13);
            avro::encode(e, v.RadialHarmonicN2A24);
            avro::encode(e, v.RadialHarmonicN2824);
            avro::encode(e, v.RadialHarmonicN2A57);
            avro::encode(e, v.RadialHarmonicN2B57);
            avro::encode(e, v.AxialHarmonicN2A);
            avro::encode(e, v.AxialHarmonicN2B);
        }
        static void decode(Decoder& d, c::channels& v) {
            if (avro::ResolvingDecoder *rd =
                    dynamic_cast<avro::ResolvingDecoder *>(&d)) {
                const std::vector<size_t> fo = rd->fieldOrder();
                for (std::vector<size_t>::const_iterator it = fo.begin();
                     it != fo.end(); ++it) {
                    switch (*it) {
                        case 0:
                            avro::decode(d, v.PositionV13);
                            break;
                        case 1:
                            avro::decode(d, v.PositionW13);
                            break;
                        case 2:
                            avro::decode(d, v.PositionV24);
                            break;
                        case 3:
                            avro::decode(d, v.PositionW24);
                            break;
                        case 4:
                            avro::decode(d, v.PositionV57);
                            break;
                        case 5:
                            avro::decode(d, v.PositionW57);
                            break;
                        case 6:
                            avro::decode(d, v.Positionz1);
                            break;
                        case 7:
                            avro::decode(d, v.PositionZ12);
                            break;
                        case 8:
                            avro::decode(d, v.CommandeV1);
                            break;
                        case 9:
                            avro::decode(d, v.CommandeV3);
                            break;
                        case 10:
                            avro::decode(d, v.CommandeV2);
                            break;
                        case 11:
                            avro::decode(d, v.CommandeV4);
                            break;
                        case 12:
                            avro::decode(d, v.CommandeV5);
                            break;
                        case 13:
                            avro::decode(d, v.CommandeV7);
                            break;
                        case 14:
                            avro::decode(d, v.CommandeW1);
                            break;
                        case 15:
                            avro::decode(d, v.CommandeW3);
                            break;
                        case 16:
                            avro::decode(d, v.CommandeW2);
                            break;
                        case 17:
                            avro::decode(d, v.CommandeW4);
                            break;
                        case 18:
                            avro::decode(d, v.CommandeW5);
                            break;
                        case 19:
                            avro::decode(d, v.CommandeW7);
                            break;
                        case 20:
                            avro::decode(d, v.Commandez1);
                            break;
                        case 21:
                            avro::decode(d, v.CommandeZ2);
                            break;
                        case 22:
                            avro::decode(d, v.TDCBit);
                            break;
                        case 23:
                            avro::decode(d, v.CurrentV1);
                            break;
                        case 24:
                            avro::decode(d, v.CurrentV3);
                            break;
                        case 25:
                            avro::decode(d, v.CurrentV2);
                            break;
                        case 26:
                            avro::decode(d, v.CurrentV4);
                            break;
                        case 27:
                            avro::decode(d, v.CurrentV5);
                            break;
                        case 28:
                            avro::decode(d, v.CurrentV7);
                            break;
                        case 29:
                            avro::decode(d, v.CurrentW1);
                            break;
                        case 30:
                            avro::decode(d, v.CurrentW3);
                            break;
                        case 31:
                            avro::decode(d, v.CurrentW2);
                            break;
                        case 32:
                            avro::decode(d, v.CurrentW4);
                            break;
                        case 33:
                            avro::decode(d, v.CurrentW5);
                            break;
                        case 34:
                            avro::decode(d, v.CurrentW7);
                            break;
                        case 35:
                            avro::decode(d, v.CurrentZ1);
                            break;
                        case 36:
                            avro::decode(d, v.CurrentZ2);
                            break;
                        case 37:
                            avro::decode(d, v.CurrentZ3);
                            break;
                        case 38:
                            avro::decode(d, v.CurrentZ4);
                            break;
                        case 39:
                            avro::decode(d, v.Rotation_Frequency_A);
                            break;
                        case 40:
                            avro::decode(d, v.Rotation_Frequency_B);
                            break;
                        case 41:
                            avro::decode(d, v.SPV_speed_A);
                            break;
                        case 42:
                            avro::decode(d, v.SPV_speed_B);
                            break;
                        case 43:
                            avro::decode(d, v.UnbalanceA13);
                            break;
                        case 44:
                            avro::decode(d, v.UnbalanceB13);
                            break;
                        case 45:
                            avro::decode(d, v.UnbalanceA24);
                            break;
                        case 46:
                            avro::decode(d, v.UnbalanceB24);
                            break;
                        case 47:
                            avro::decode(d, v.UnbalanceA57);
                            break;
                        case 48:
                            avro::decode(d, v.UnbalanceB57);
                            break;
                        case 49:
                            avro::decode(d, v.AxialHarmonic1A);
                            break;
                        case 50:
                            avro::decode(d, v.AxialHarmonic1B);
                            break;
                        case 51:
                            avro::decode(d, v.MachineTemp_1_A);
                            break;
                        case 52:
                            avro::decode(d, v.MachineTemp_2_A);
                            break;
                        case 53:
                            avro::decode(d, v.MachineTemp_3_A);
                            break;
                        case 54:
                            avro::decode(d, v.MachineTemp_4_A);
                            break;
                        case 55:
                            avro::decode(d, v.MachineTemp_5_A);
                            break;
                        case 56:
                            avro::decode(d, v.MachineTemp_6_A);
                            break;
                        case 57:
                            avro::decode(d, v.MachineTemp_7_A);
                            break;
                        case 58:
                            avro::decode(d, v.MachineTemp_8_A);
                            break;
                        case 59:
                            avro::decode(d, v.MachineTemp_1_B);
                            break;
                        case 60:
                            avro::decode(d, v.MachineTemp_2_B);
                            break;
                        case 61:
                            avro::decode(d, v.MachineTemp_3_B);
                            break;
                        case 62:
                            avro::decode(d, v.MachineTemp_4_B);
                            break;
                        case 63:
                            avro::decode(d, v.MachineTemp_5_B);
                            break;
                        case 64:
                            avro::decode(d, v.MachineTemp_6_B);
                            break;
                        case 65:
                            avro::decode(d, v.MachineTemp_7_B);
                            break;
                        case 66:
                            avro::decode(d, v.MachineTemp_8_B);
                            break;
                        case 67:
                            avro::decode(d, v.coilTempV1);
                            break;
                        case 68:
                            avro::decode(d, v.coilTempV3);
                            break;
                        case 69:
                            avro::decode(d, v.coilTempv2);
                            break;
                        case 70:
                            avro::decode(d, v.coilTempv4);
                            break;
                        case 71:
                            avro::decode(d, v.coilTempv5);
                            break;
                        case 72:
                            avro::decode(d, v.coilTempV7);
                            break;
                        case 73:
                            avro::decode(d, v.coilTempw1);
                            break;
                        case 74:
                            avro::decode(d, v.coilTempW3);
                            break;
                        case 75:
                            avro::decode(d, v.coilTempW2);
                            break;
                        case 76:
                            avro::decode(d, v.coilTempW4);
                            break;
                        case 77:
                            avro::decode(d, v.coilTempW5);
                            break;
                        case 78:
                            avro::decode(d, v.coilTempW7);
                            break;
                        case 79:
                            avro::decode(d, v.coilTempZI);
                            break;
                        case 80:
                            avro::decode(d, v.coilTempZ2);
                            break;
                        case 81:
                            avro::decode(d, v.coilTempz3);
                            break;
                        case 82:
                            avro::decode(d, v.coilTempZ4);
                            break;
                        case 83:
                            avro::decode(d, v.peakPositionv13);
                            break;
                        case 84:
                            avro::decode(d, v.peakPositionW13);
                            break;
                        case 85:
                            avro::decode(d, v.peakPositionV24);
                            break;
                        case 86:
                            avro::decode(d, v.peakPositionW24);
                            break;
                        case 87:
                            avro::decode(d, v.peakPositionV57);
                            break;
                        case 88:
                            avro::decode(d, v.peakPositionW57);
                            break;
                        case 89:
                            avro::decode(d, v.peakPositionz1);
                            break;
                        case 90:
                            avro::decode(d, v.peakPosition22);
                            break;
                        case 91:
                            avro::decode(d, v.PeakElongation_Rotor_SPV);
                            break;
                        case 92:
                            avro::decode(d, v.VDCMains);
                            break;
                        case 93:
                            avro::decode(d, v.VDCPA_V13);
                            break;
                        case 94:
                            avro::decode(d, v.VDCPA_W13);
                            break;
                        case 95:
                            avro::decode(d, v.VDCPA_V24);
                            break;
                        case 96:
                            avro::decode(d, v.VDCPA_W24);
                            break;
                        case 97:
                            avro::decode(d, v.VDCPA_V57);
                            break;
                        case 98:
                            avro::decode(d, v.VDCPA_W57);
                            break;
                        case 99:
                            avro::decode(d, v.VDCPA_Z12);
                            break;
                        case 100:
                            avro::decode(d, v.VDCPA_234);
                            break;
                        case 101:
                            avro::decode(d, v.AmplifierTempv13);
                            break;
                        case 102:
                            avro::decode(d, v.AmplifierTempW13);
                            break;
                        case 103:
                            avro::decode(d, v.AmplifierTempv24);
                            break;
                        case 104:
                            avro::decode(d, v.AmplifierTempW24);
                            break;
                        case 105:
                            avro::decode(d, v.AmplifierTempV57);
                            break;
                        case 106:
                            avro::decode(d, v.AmplifierTempW57);
                            break;
                        case 107:
                            avro::decode(d, v.AmplifierTempz12);
                            break;
                        case 108:
                            avro::decode(d, v.AmplifierTempz34);
                            break;
                        case 109:
                            avro::decode(d, v.ISO_Bear_A);
                            break;
                        case 110:
                            avro::decode(d, v.ISO_Det_A);
                            break;
                        case 111:
                            avro::decode(d, v.ISO_Bear_B);
                            break;
                        case 112:
                            avro::decode(d, v.ISO_Det_B);
                            break;
                        case 113:
                            avro::decode(d, v.RadialHarmonicN2A13);
                            break;
                        case 114:
                            avro::decode(d, v.RadialHarmonicN2B13);
                            break;
                        case 115:
                            avro::decode(d, v.RadialHarmonicN2A24);
                            break;
                        case 116:
                            avro::decode(d, v.RadialHarmonicN2824);
                            break;
                        case 117:
                            avro::decode(d, v.RadialHarmonicN2A57);
                            break;
                        case 118:
                            avro::decode(d, v.RadialHarmonicN2B57);
                            break;
                        case 119:
                            avro::decode(d, v.AxialHarmonicN2A);
                            break;
                        case 120:
                            avro::decode(d, v.AxialHarmonicN2B);
                            break;
                        default:
                            break;
                    }
                }
            } else {
                avro::decode(d, v.PositionV13);
                avro::decode(d, v.PositionW13);
                avro::decode(d, v.PositionV24);
                avro::decode(d, v.PositionW24);
                avro::decode(d, v.PositionV57);
                avro::decode(d, v.PositionW57);
                avro::decode(d, v.Positionz1);
                avro::decode(d, v.PositionZ12);
                avro::decode(d, v.CommandeV1);
                avro::decode(d, v.CommandeV3);
                avro::decode(d, v.CommandeV2);
                avro::decode(d, v.CommandeV4);
                avro::decode(d, v.CommandeV5);
                avro::decode(d, v.CommandeV7);
                avro::decode(d, v.CommandeW1);
                avro::decode(d, v.CommandeW3);
                avro::decode(d, v.CommandeW2);
                avro::decode(d, v.CommandeW4);
                avro::decode(d, v.CommandeW5);
                avro::decode(d, v.CommandeW7);
                avro::decode(d, v.Commandez1);
                avro::decode(d, v.CommandeZ2);
                avro::decode(d, v.TDCBit);
                avro::decode(d, v.CurrentV1);
                avro::decode(d, v.CurrentV3);
                avro::decode(d, v.CurrentV2);
                avro::decode(d, v.CurrentV4);
                avro::decode(d, v.CurrentV5);
                avro::decode(d, v.CurrentV7);
                avro::decode(d, v.CurrentW1);
                avro::decode(d, v.CurrentW3);
                avro::decode(d, v.CurrentW2);
                avro::decode(d, v.CurrentW4);
                avro::decode(d, v.CurrentW5);
                avro::decode(d, v.CurrentW7);
                avro::decode(d, v.CurrentZ1);
                avro::decode(d, v.CurrentZ2);
                avro::decode(d, v.CurrentZ3);
                avro::decode(d, v.CurrentZ4);
                avro::decode(d, v.Rotation_Frequency_A);
                avro::decode(d, v.Rotation_Frequency_B);
                avro::decode(d, v.SPV_speed_A);
                avro::decode(d, v.SPV_speed_B);
                avro::decode(d, v.UnbalanceA13);
                avro::decode(d, v.UnbalanceB13);
                avro::decode(d, v.UnbalanceA24);
                avro::decode(d, v.UnbalanceB24);
                avro::decode(d, v.UnbalanceA57);
                avro::decode(d, v.UnbalanceB57);
                avro::decode(d, v.AxialHarmonic1A);
                avro::decode(d, v.AxialHarmonic1B);
                avro::decode(d, v.MachineTemp_1_A);
                avro::decode(d, v.MachineTemp_2_A);
                avro::decode(d, v.MachineTemp_3_A);
                avro::decode(d, v.MachineTemp_4_A);
                avro::decode(d, v.MachineTemp_5_A);
                avro::decode(d, v.MachineTemp_6_A);
                avro::decode(d, v.MachineTemp_7_A);
                avro::decode(d, v.MachineTemp_8_A);
                avro::decode(d, v.MachineTemp_1_B);
                avro::decode(d, v.MachineTemp_2_B);
                avro::decode(d, v.MachineTemp_3_B);
                avro::decode(d, v.MachineTemp_4_B);
                avro::decode(d, v.MachineTemp_5_B);
                avro::decode(d, v.MachineTemp_6_B);
                avro::decode(d, v.MachineTemp_7_B);
                avro::decode(d, v.MachineTemp_8_B);
                avro::decode(d, v.coilTempV1);
                avro::decode(d, v.coilTempV3);
                avro::decode(d, v.coilTempv2);
                avro::decode(d, v.coilTempv4);
                avro::decode(d, v.coilTempv5);
                avro::decode(d, v.coilTempV7);
                avro::decode(d, v.coilTempw1);
                avro::decode(d, v.coilTempW3);
                avro::decode(d, v.coilTempW2);
                avro::decode(d, v.coilTempW4);
                avro::decode(d, v.coilTempW5);
                avro::decode(d, v.coilTempW7);
                avro::decode(d, v.coilTempZI);
                avro::decode(d, v.coilTempZ2);
                avro::decode(d, v.coilTempz3);
                avro::decode(d, v.coilTempZ4);
                avro::decode(d, v.peakPositionv13);
                avro::decode(d, v.peakPositionW13);
                avro::decode(d, v.peakPositionV24);
                avro::decode(d, v.peakPositionW24);
                avro::decode(d, v.peakPositionV57);
                avro::decode(d, v.peakPositionW57);
                avro::decode(d, v.peakPositionz1);
                avro::decode(d, v.peakPosition22);
                avro::decode(d, v.PeakElongation_Rotor_SPV);
                avro::decode(d, v.VDCMains);
                avro::decode(d, v.VDCPA_V13);
                avro::decode(d, v.VDCPA_W13);
                avro::decode(d, v.VDCPA_V24);
                avro::decode(d, v.VDCPA_W24);
                avro::decode(d, v.VDCPA_V57);
                avro::decode(d, v.VDCPA_W57);
                avro::decode(d, v.VDCPA_Z12);
                avro::decode(d, v.VDCPA_234);
                avro::decode(d, v.AmplifierTempv13);
                avro::decode(d, v.AmplifierTempW13);
                avro::decode(d, v.AmplifierTempv24);
                avro::decode(d, v.AmplifierTempW24);
                avro::decode(d, v.AmplifierTempV57);
                avro::decode(d, v.AmplifierTempW57);
                avro::decode(d, v.AmplifierTempz12);
                avro::decode(d, v.AmplifierTempz34);
                avro::decode(d, v.ISO_Bear_A);
                avro::decode(d, v.ISO_Det_A);
                avro::decode(d, v.ISO_Bear_B);
                avro::decode(d, v.ISO_Det_B);
                avro::decode(d, v.RadialHarmonicN2A13);
                avro::decode(d, v.RadialHarmonicN2B13);
                avro::decode(d, v.RadialHarmonicN2A24);
                avro::decode(d, v.RadialHarmonicN2824);
                avro::decode(d, v.RadialHarmonicN2A57);
                avro::decode(d, v.RadialHarmonicN2B57);
                avro::decode(d, v.AxialHarmonicN2A);
                avro::decode(d, v.AxialHarmonicN2B);
            }
        }
    };

}
#endif
