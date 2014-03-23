

#ifndef __DIFF_LIBRARY_DIFF_H
#define __DIFF_LIBRARY_DIFF_H




namespace DiffLibrary
{
    template<typename _TyElement>
    class IsEqual
    {
    public:
        typedef _TyElement ElementType;
      
        inline bool operator()(const ElementType &left_param, 
            const ElementType &right_param)const
        {
            return left_param == right_param;
        }
    };


    template<typename _TyElement,
        class _TyContainer = std::vector<_TyElement>, 
        class _TyComparator = IsEqual<_TyElement>>
    class Diff
    {
    public:
        typedef _TyElement ElementType;
        typedef _TyContainer ContainerType;
        typedef _TyComparator ComparatorType;
        typedef Ses<ElementType> SesType;



        Diff(const ContainerType &m, const ContainerType &n)
            : param_m_(m)
            , param_n_(n)
            , is_swap_(false)
        {
            if (param_m_.size() >= param_n_.size())
            {
                std::swap(param_m_, param_n_);
                is_swap_ = true;
            }
        }

        ~Diff()
        {
        }


        const SesType &GetSes()const
        {
            return ses_;
        }


        void Compose()
        {
            const CoordinateType length_m((CoordinateType)param_m_.size());
            const CoordinateType length_n((CoordinateType)param_n_.size());
            const CoordinateType delta(length_n - length_m);
            const CoordinateType offset(length_m + 1);

            // length_m + 1 + length _n + 1 + 1 
            PathArray fp(length_m + length_n + 3, -1); 
            PathArray path(fp.size(), -1);
            PathCoordinates coordinates;
            CoordinateType p(-1);
            do 
            {
                ++p;
                for (CoordinateType k = -p; k <= delta - 1; ++k)
                {
                    fp[k + offset] = Snake(k, 
                        fp[k - 1 + offset] + 1, 
                        fp[k + 1 + offset], 
                        path, 
                        coordinates);
                }
                for (CoordinateType k = delta + p; k >= delta + 1; --k)
                {
                    fp[k + offset] = Snake(k, 
                        fp[k - 1 + offset] + 1,
                        fp[k + 1 + offset],
                        path,
                        coordinates);
                }
                fp[delta + offset] = Snake(delta, 
                    fp[delta - 1 + offset] + 1,
                    fp[delta + 1 + offset],
                    path,
                    coordinates);
            } while (fp[delta + offset] != length_n);

            SesFormPathCoordinate(path[delta + offset], coordinates);
        }




    protected:
        CoordinateType Snake(const CoordinateType k,
            const CoordinateType above, 
            const CoordinateType below,
            PathArray &path,
            PathCoordinates &coordinates)const
        {
            CoordinateType y(std::max(above, below));
            CoordinateType x(y - k);
            while ((size_t)x < param_m_.size() && 
                (size_t)y < param_n_.size() && 
                comparator_(param_m_[(size_t)x], param_n_[(size_t)y]))
            {
                ++x;
                ++y;
            }

            {
                const CoordinateType offset((CoordinateType)param_m_.size() + 1);
                const CoordinateType r(above > below ?
                    path[(size_t)k - 1 + offset] :
                    path[(size_t)k + 1 + offset]);
                path[(size_t)k + offset] = (CoordinateType)coordinates.size(); 
                coordinates.push_back(Point(x, y, r));
            }
            return y;
        }

        void SesFormPathCoordinate(CoordinateType r, 
            const PathCoordinates &coordinates)
        {
            PathCoordinates pc;
            for (; r != -1; r = coordinates[(size_t)r].k)
            {
                pc.push_back(coordinates[(size_t)r]);
            }

            auto x(param_m_.cbegin());
            auto y(param_n_.cbegin());
            CoordinateType x_idx, y_idx;   // line number for Unified Format
            CoordinateType px_idx, py_idx; // coordinates
            x_idx = y_idx = 1;
            px_idx = py_idx = 0;
            for (CoordinateType i = (CoordinateType)pc.size() - 1; i >= 0; --i)
            {
                while (px_idx < pc[i].x || py_idx < pc[i].y)
                {
                    if (pc[i].y - pc[i].x > py_idx - px_idx)
                    {
                        if (!is_swap_) 
                        {
                            ses_.AddSequence(*y, 0, y_idx, EditInfo::kAdd);
                        }
                        else {
                            ses_.AddSequence(*y, y_idx, 0, EditInfo::kDelete);
                        }
                        ++y;
                        ++y_idx;
                        ++py_idx;
                    }
                    else if (pc[i].y - pc[i].x < py_idx - px_idx)
                    {
                        if (!is_swap_) 
                        {
                            ses_.AddSequence(*x, x_idx, 0, EditInfo::kDelete);
                        }
                        else {
                            ses_.AddSequence(*x, 0, x_idx, EditInfo::kAdd);
                        }
                        ++x;
                        ++x_idx;
                        ++px_idx;
                    }
                    else {
                        ses_.AddSequence(is_swap_? *y: *x, 
                            x_idx, 
                            y_idx, 
                            EditInfo::kCommon);
                        ++x;
                        ++y;
                        ++x_idx;
                        ++y_idx;
                        ++px_idx;
                        ++py_idx;
                    }
                }
            }
        }





        ContainerType param_m_;
        ContainerType param_n_;
        bool is_swap_;
        Ses<ElementType> ses_;

        ComparatorType comparator_;
    };

}

#endif
