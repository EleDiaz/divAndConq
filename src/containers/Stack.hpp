#include "List.hpp"

template <class DATO>
class Stack : private List<DATO> {
public:
    using List<DATO>::isEmpty;
    using List<DATO>::push;
    using List<DATO>::pop;
    using List<DATO>::map;
};
