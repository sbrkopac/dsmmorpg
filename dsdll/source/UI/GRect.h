
#ifndef _GRECT_H_
#define _GRECT_G_

    #include "../GPG.h"

    class GRect
    {
        FEX int GetLeft() const
        {
            return ((RECT*)this)->left;
        }

        FEX int GetTop() const
        {
            return ((RECT*)this)->top;
        }

        FEX int GetRight() const
        {
            return ((RECT*)this)->right;
        }

        FEX int GetBottom() const
        {
            return ((RECT*)this)->bottom;
        }

        FEX void SetLeft( int left )
        {
            ((RECT*)this)->left = left;
        }

        FEX void SetTop( int top )
        {
            ((RECT*)this)->top = top;
        }

        FEX void SetRight( int right )
        {
            ((RECT*)this)->right = right;
        }

        FEX void SetBottom( int bottom )
        {
            ((RECT*)this)->bottom = bottom;
        }
    };

#endif