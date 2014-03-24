

#ifndef __DIFF_LIBRARY_TYPES_H
#define __DIFF_LIBRARY_TYPES_H

namespace DiffLibrary
{
    typedef int CoordinateType;
    
    struct Point
    {
        CoordinateType x;
        CoordinateType y;
        CoordinateType k;

        Point(const CoordinateType data_x = -1,
            const CoordinateType data_y = -1,
            const CoordinateType data_k = -1)
            : x(data_x)
            , y(data_y)
            , k(data_k)
        {
        }
    };
 
    typedef std::vector<CoordinateType> PathArray;
    typedef std::vector<Point> PathCoordinates;


    struct EditInfo
    {
        CoordinateType indexBefore;
        CoordinateType indexAfter;
        typedef enum _EditType
        {
            kAdd = 0,
            kDelete,
            kCommon,
        }EditType;
        EditType editType;

        EditInfo(const CoordinateType before,
            const CoordinateType after,
            EditType edit_type)
            : indexBefore(before)
            , indexAfter(after)
            , editType(edit_type)
        {
        }
    };

    static const std::string kAddString = "+";
    static const std::string kDeleteString = "-";
    static const std::string kCommonString = "";
}

#endif
