

#ifndef __DIFF_LIBRARY_SES_H
#define __DIFF_LIBRARY_SES_H

namespace DiffLibrary
{
    template<typename _TyString>
    struct StringHelper
    {
        typedef _TyString StringType;

        inline StringType operator()(StringType str)
        {
            return str;
        }
    };

    template<>
    struct StringHelper<std::string>
    {
        typedef std::string StringType;

        inline const StringType::value_type *operator()(const StringType &str)
        {
            return str.c_str();
        }
    };


    template<typename _TyData, 
        typename _TyStream = std::ostream>
    class SesSerialize
    {
    public:
        typedef _TyData DataType;
        typedef _TyStream StreamType;


        SesSerialize(StreamType &out)
            : out_stream_(out)
        {
        }

        void operator()(const DataType &data)const
        {
            typedef StringHelper<DataType::first_type> Helper;

            switch (data.second.editType) {
            case EditInfo::kAdd:
                out_stream_ << kAddString.c_str() << Helper()(data.first) << endl;
                break;
            case EditInfo::kDelete:
                out_stream_ << kDeleteString.c_str() << Helper()(data.first) << endl;
                break;
            case EditInfo::kCommon:
                out_stream_ << kCommonString.c_str() << Helper()(data.first) << endl;
                break;
            }
        }


    protected:
        StreamType &out_stream_;
    };


    template<typename _TyElement>
    class Ses
    {
    public:
        typedef _TyElement ElementType;
        typedef std::pair<ElementType, EditInfo> EditPair;
        typedef std::vector<EditPair> EditSequence;


        Ses()
        {
        }

        ~Ses()
        {
        }

        const EditSequence &GetSequence()const
        {
            return sequence_;
        }

        void AddSequence(const EditPair& data)
        {
            sequence_.push_back(data);
        }

        void AddSequence(ElementType ele, 
            CoordinateType before_idx, 
            CoordinateType after_idx, 
            const EditInfo::EditType type)
        {
            AddSequence(EditPair(ele,
                EditInfo(before_idx, 
                    after_idx, 
                    type)));
        }

        template<typename _TyStream>
        void Serialize(_TyStream &out)const
        {
            for_each(sequence_.begin(), 
                sequence_.end(),
                SesSerialize<EditPair, _TyStream>(out));
        }




    protected:
        EditSequence sequence_;
    };
}

#endif
