ofxDotFrag
=====================================
[![Build status](https://travis-ci.org/npisanti/ofxDotFrag.svg?branch=master)](https://travis-ci.org/npisanti/ofxDotFrag) [![Build status](https://ci.appveyor.com/api/projects/status/aihs37lryw28va92?svg=true)](https://ci.appveyor.com/project/npisanti/ofxdotfrag)

ofxDotFrag is a collection of ready to use post processing / glitch shaders with this goals:
- Process and renders to `ofFbo`s.
- Cross compatible, works both on openGL and openGL ES
- Fast to use API ( higher level than just using ofShader )
- Shaders made to be used/tweaked in realtime performances
- Easy to write new shader classes

At the moment the shader selection includes:
- Hue/Saturation/Brightness/Contrast
- ThreeTones
- Delay
- EchoTrace
- InvertStrobe
- Mirror
- MirrorAxis
- Turbolence
- FXAA
- Twist
- RadialRemap    

and an `ofx::dotfrag::Live` class for live coding.

Donate
------------ 
I support you, you support me!    
If you find this code useful, consider [fueling me with coffee](https://ko-fi.com/npisanti)!

License
------------ 
Nicola Pisanti, MIT License 2018-2019.   
