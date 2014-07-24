#include <cstdint>
#include <string>

namespace bson {
    class Document;
}

namespace mongo {
namespace driver {

    /**
     * ReadModel
     */
    class ReadPreference;

    template <class Derived>
    class ReadModel {

    public:
        Derived& read_preference(const ReadPreference* read_preference);
        const ReadPreference* read_preference();

    protected:
        ReadPreference* _read_preference;
    }


    /**
     * WriteModel
     */
    class WriteConcern;

    template <class Derived>
    class WriteModel {

    public:
        Derived& write_concern(const WriteConcern* write_concern);
        WriteConcern write_concern();

    protected:
        WriteConcern* _write_concern;

    };

    /**
     * FindAndRemoveModel
     */
    class FindAndRemoveModel : public WriteModel<FindAndRemoveModel> {

    public:
        FindAndRemoveModel(const bson::Document& filter);

        FindAndRemoveModel& projection(const bson::Document& projection);
        FindAndRemoveModel& sort(const bson::Document& ordering);

    private:
        const bson::Document& _filter;

        bson::Document& _projection;
        bson::Document& _ordering;

    };

    /**
     * FindModel
     */
    class FindModel : public ReadModel<FindModel> {

    public:
        FindModel(const bson::Document& filter);

        FindModel& batch_size(int32_t batch_size);
        FindModel& cursor_flags(int32_t cursor_flags);
        FindModel& limit(int32_t limit);
        FindModel& modifiers(const bson::Document& modifiers);
        FindModel& projection(const bson::Document& projection);
        FindModel& skip(int32_t skip);
        FindModel& sort(const bson::Document& sort);
        FindModel& max_time_ms(int64_t max_time_ms);

        // TODO: breakup modifiers in spec or continue and add members?
        FindModel& min(const bson::Document& min);
        FindModel& max(const bson::Document& max);
        FindModel& hint(const bson::Document& hint);
        FindModel& returnKey(bool return_key);
        FindModel& snapshot(bool snapshot);
        FindModel& show_disk_loc(bool show_disk_loc);
        FindModel& comment(const std::string& comment);
        FindModel& max_scan(int64_t max_scan);

    private:
        const bson::Document& _filter;

        int32_t _batch_size;
        int32_t _cursor_flags;
        int32_t _limit;
        bson::Document& _modifiers;
        bson::Document& _projection;
        int32_t _skip;
        bson::Document& _sort;
        int64_t _max_time_ms;
    };

    class Operation {
    public:
        // TODO: pure virtual interface
    };

    class QueryOperation {
    public:
        QueryOperation(const FindModel& model);
    private:
        const FindModel& _model;
    };

    class FindAndModifyOperation {
    public:
        FindAndModifyOperation(const FindAndRemoveModel& model);
        FindAndModifyOperation(const FindAndUpdateModel& model);
        FindAndModifyOperation(const FindAndReplaceModel& model);
    private:
        const FindModel& _model;
    };

}
}
