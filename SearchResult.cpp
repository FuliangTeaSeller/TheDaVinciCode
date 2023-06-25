#include "SearchResult.h"

SearchResult::SearchResult():guessList((MAX_CARD_NUM + JOCKER) * 2),bestResult(std::make_pair(-1, -1.0))
{
}
