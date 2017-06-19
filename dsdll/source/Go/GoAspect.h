
#ifndef _GOASPECT_H_
#define _GOASPECT_H_

    // Include Libraries

    #include "../GPG.h"

    enum ePlayerSkin
    {
        PS_FLESH = 0,
        PS_CLOTH,
    };

    FEX ePlayerSkin MakePlayerSkin (int ps)
    {
        return (ePlayerSkin)ps;
    }

    class GoAspect
    {
        public:

            FEX void SetRenderScale (float value)
            {
                float *address = (float*) this;

                address[0x06] = value;
            }

            FEX const char * GetDynamicTexture (int skin) const
            {
                gp_string **address = (gp_string **) this;

                if (skin == PS_FLESH)
                        return address[0x0a]->c_str();
                else if (skin == PS_CLOTH)
                        return address[0x0b]->c_str();
                else
                        return "";
            }
    };

#endif