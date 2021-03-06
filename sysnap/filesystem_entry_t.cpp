#include "filesystem_entry_t.hpp"

namespace sysnap {
	/*---> CONSTRUCTOR <---*/
	FileSystemEntry_t::FileSystemEntry_t() {
		this->name_m					= "";
		this->path_m					= "";

		this->date_modified_m.day		= 0;
		this->date_modified_m.month		= 0;
		this->date_modified_m.year		= 0;
		this->date_modified_m.hour		= 0;
		this->date_modified_m.minute	= 0;
		this->date_modified_m.second	= 0;
		this->date_modified_m.zone		= (char*)"";

		this->permissions_m.owner		= 0;
		this->permissions_m.group		= 0;
		this->permissions_m.others		= 0;

		this->owner_m					= "";
		this->group_m					= "";

		this->size_m					= 0;

		this->file_type_m				= REGULAR_FILE;

		//this->content_m.clear();
	}

	FileSystemEntry_t::~FileSystemEntry_t() {
		if(!this->content_m.empty()) {
			this->content_m.clear();
		}
	}

	/*---> SETTERS <---*/
	void FileSystemEntry_t::iNode(unsigned long _iNode) {
		this->iNode_m = _iNode;
	}
	void FileSystemEntry_t::Name(std::string _name) {
		this->name_m = _name;
	}

	void FileSystemEntry_t::Path(std::string _path) {
		this->path_m = _path;
	}

	void FileSystemEntry_t::Path(Path_t _path) {
		this->path_m = _path;
	}

	void FileSystemEntry_t::DateModified(Timestamp_t _date_modified) {
		this->date_modified_m = _date_modified;
	}

	void FileSystemEntry_t::DateModified(int _day, int _month, int _year,
									   int _hour, int _minute, int _second,
									   char* _zone) {
		this->date_modified_m.day		= _day;
		this->date_modified_m.month		= _month;
		this->date_modified_m.year		= _year;
		this->date_modified_m.hour		= _hour;
		this->date_modified_m.minute	= _minute;
		this->date_modified_m.second	= _second;
		this->date_modified_m.zone		= _zone;
	}

	void FileSystemEntry_t::Permissions(PermissionsFlag_t _permissions) {
		this->permissions_m = _permissions;
	}

	void FileSystemEntry_t::Permissions(int _permissions) {
		this->permissions_m = sysnap::GetPermissionsFlag(_permissions);
	}

	void FileSystemEntry_t::Permissions(int _owner, int _group, int _others) {
		this->permissions_m.owner	= _owner;
		this->permissions_m.group	= _group;
		this->permissions_m.others	= _others;
	}

	void FileSystemEntry_t::Owner(std::string _owner) {
		this->owner_m = _owner;
	}

	void FileSystemEntry_t::Group(std::string _group) {
		this->group_m = _group;
	}

	void FileSystemEntry_t::Size(unsigned long _size) {
		this->size_m = _size;
	}

	void FileSystemEntry_t::FileType(UNIX_FILE_t _file_type) {
		this->file_type_m = _file_type;
	}

	void FileSystemEntry_t::InsertContent(FileSystemEntry_t* _fs_entry) {
		this->content_m.push_back(_fs_entry);
	}

	/*---> GETTERS <---*/
	unsigned long 					FileSystemEntry_t::iNode() {
			return this->iNode_m;
	}

	std::string						FileSystemEntry_t::Name() {
		return this->name_m;
	}

	Path_t							FileSystemEntry_t::Path() {
		return this->path_m;
	}

	Timestamp_t						FileSystemEntry_t::DateModified() {
		return this->date_modified_m;
	}

	PermissionsFlag_t				FileSystemEntry_t::Permissions() {
		return this->permissions_m;
	}

	std::string						FileSystemEntry_t::Owner() {
		return this->owner_m;
	}

	std::string						FileSystemEntry_t::Group() {
		return this->group_m;
	}

	unsigned long					FileSystemEntry_t::Size() {
		return this->size_m;
	}

	UNIX_FILE_t						FileSystemEntry_t::FileType() {
		return this->file_type_m;
	}

	std::vector<FileSystemEntry_t*>	FileSystemEntry_t::Content() {
		return this->content_m;
	}

	FileSystemEntry_t*				FileSystemEntry_t::Find(std::string _name) {
		for(std::vector<FileSystemEntry_t*>::iterator iter = this->content_m.begin();
		iter != this->content_m.end();
		iter++) {
			if((*iter)->Name() == _name) {
				return *iter;
			}
		}

		return NULL;
	}

	bool 							FileSystemEntry_t::Empty() {
		return this->content_m.empty();
	}

	/*---> OPERATORS <---*/
	FileSystemEntry_t& 				FileSystemEntry_t::operator[](int _index) {
		return *this->content_m[_index];
	}

	FileSystemEntry_t&				FileSystemEntry_t::operator[](std::string _name) {
		return *(this->Find(_name));
	}
}
