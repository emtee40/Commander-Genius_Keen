/*
	OpenLieroX

	INI reader

	18-01-2008, by Albert Zeyer
	code under LGPL
*/

#ifndef __INI_READER_H__
#define __INI_READER_H__

#include <base/interface/StringUtils.h>
#include <map>
#include <set>

struct GsColor;

/*
	to use this class, you have to create a subclass from it and
	overload the OnNewSection or/and OnEntry
*/
class IniReader {
public:
	typedef std::map<std::string, int, stringcaseless> KeywordList;


	IniReader(const std::string& filename, KeywordList& keywords = IniReader::DefaultKeywords);
	virtual ~IniReader();

	// returns false if there was an error
	// if you break via the callbacks, this is also an error
    virtual bool Parse();

	// if the return value is false, the parsing will break
    virtual bool OnNewSection (const std::string&) { return true; }
    virtual bool OnEntry (const std::string&,
                          const std::string&,
                          const std::string& ) { return true; }

	// Reading
	bool ReadString(const std::string& section, const std::string& key, std::string& value, std::string defaultv) const;
	bool ReadInteger(const std::string& section, const std::string& key, int *value, int defaultv) const;
	bool ReadFloat(const std::string& section, const std::string& key, float *value, float defaultv) const;
	bool ReadIntArray(const std::string& section, const std::string& key, int *array, int num_items) const;
	bool ReadColour(const std::string& section, const std::string& key, GsColor& value, const GsColor& defaultv) const;
	bool ReadKeyword(const std::string& section, const std::string& key, int *value, int defaultv) const;
	bool ReadKeyword(const std::string& section, const std::string& key, bool *value, bool defaultv) const;
	bool ReadKeywordList(const std::string& section, const std::string& key, int *value, int defaultv)const;

	template<typename T>
	bool ReadArray(const std::string& section, const std::string& key, T* data, size_t num) const {
		std::string string;

		if (!ReadString(section, key, string, ""))
			return false;

		std::vector<std::string> arr = explode(string,",");
		for (size_t i=0; i< MIN(num,arr.size()); i++)
			data[i] = from_string<T>(arr[i]);

		return num == arr.size();
	}

	// Keyword
	std::string getFileName() const { return m_filename; }

    std::set<std::string> getSectionList();

	static KeywordList DefaultKeywords;
protected:
	std::string m_filename;
	KeywordList& m_keywords;

public:
	typedef std::map<std::string, std::string> Section;
	typedef std::map<std::string, Section> SectionMap;
	SectionMap m_sections;

private:
	Section *m_curSection;

private:
	bool GetString(const std::string& section, const std::string& key, std::string& string) const;
	void NewSection(const std::string& name);
	void NewEntryInSection(const std::string& name, const std::string& value);

};

#endif

