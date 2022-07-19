

//Проверить значение заданного бита
inline bool test_bit(unsigned word, unsigned bit)
{
  return (word & (1u << bit)) != 0;
}

// Установить заданный бит
inline unsigned set_bit(unsigned word, unsigned bit)
{
  return word | (1u << bit);
}

// Сбросить заданный бит
inline unsigned reset_bit(unsigned word, unsigned bit)
{
  return word & ~(1u << bit);
}

// Поменять значение заданного бита на противоположное
inline unsigned toggle_bit(unsigned word, unsigned bit)
{
  return word ^ (1u << bit);
}

// Установить заданный бит в заданное значение
inline unsigned set_bit(unsigned word, unsigned bit, bool value)
{
  const auto mask = 1u << bit;
  return (word & ~mask) | (value? mask: 0);
}


//________________________________________________________________


//
struct struct_color_who{
    unsigned short color :16;
    unsigned short who   :16;
  };


union union_color_who{
  unsigned int int_color_who;
  struct_color_who str_color_who;
};


void unionSplit(const unsigned int colorB_whoB, unsigned short &colorFigure, unsigned short &whoFigure ){

    union_color_who unionSplit{colorB_whoB};
    colorFigure = unionSplit.str_color_who.color ;
    whoFigure =unionSplit.str_color_who.who;
};





