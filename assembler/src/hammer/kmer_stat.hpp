#ifndef HAMMER_KMERSTAT_HPP_
#define HAMMER_KMERSTAT_HPP_

#include <stdint.h>
#include <vector>
#include <map>
#include <string>

const uint32_t K = 55;
typedef uint64_t hint_t;

#define BLOBKMER_UNDEFINED	2e12
#define KMERSTAT_CHANGE		2e12
#define KMERSTAT_GOOD		2e12 + 1
#define KMERSTAT_BAD		2e12 + 2

class Read;
class PositionRead;
class PositionKMer;
class KMerStat;

typedef std::map<PositionKMer, KMerStat> KMerStatMap;
typedef std::pair<PositionKMer, KMerStat> KMerCount;
typedef std::pair<std::string, uint32_t> StringCount;


struct KMerStat {

	KMerStat (uint32_t cnt, hint_t cng, double qual) : count(cnt), changeto(cng), totalQual(qual) { }
	KMerStat () : count(0), changeto(KMERSTAT_BAD), totalQual(1) { }
	uint32_t count;
	hint_t changeto;
	double totalQual;

	bool isGood() const { return changeto == KMERSTAT_GOOD; }
	bool change() const { return changeto < KMERSTAT_CHANGE; }
};

#endif //  HAMMER_KMERSTAT_HPP_

