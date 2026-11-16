#ifndef RAYTRACER_APPLICATION_UI_CONSTANTS_H
#define RAYTRACER_APPLICATION_UI_CONSTANTS_H

namespace UIConstants
{
    /**
     * Centralizes hared layout dimensions and spacing values
     * used throughout the graphical interface 
     * to ensure consistent interface organization.
     */
    struct Layout
    {
        static constexpr int PanelMargin = 8;
        static constexpr int PanelSpacing = 10;

        static constexpr int GroupMarginHorizontal = 12;
        static constexpr int GroupMarginTop = 20;
        static constexpr int GroupMarginBottom = 12;

        static constexpr int FormHorizontalSpacing = 12;
        static constexpr int FormVerticalSpacing = 8;

        static constexpr int GroupSpacing = 10;
    };

    /**
     * Centralizes standard widget dimensions used by the application.
     */
    struct Dimensions
    {
        static constexpr int RenderButtonHeight = 55;
        static constexpr int ProgressBarHeight = 20;
    };

}


#endif // RAYTRACER_APPLICATION_UI_CONSTANTS_H