
#include <string>
#include <vector>

//#include <cppunit/Portability.h>
//#include <cppunit/portability/CppUnitSet.h>
//#include <cppunit/extensions/TestFactory.h>
#include <cppunit/TestCase.h>

#include <disambiguation.h>
#include <engine.h>
#include <cluster.h>
#include <clusterinfo.h>
#include <training.h>

#include "testdata.h"
#include "testutils.h"


class ClusterInfoTest : public CppUnit::TestCase {

private:

  list<Record> source;
  vector<string> requested_columns;

public:
  ClusterInfoTest(std::string name) : CppUnit::TestCase(name) {
    describe_test(INDENT0, name.c_str());
    requested_columns.push_back(string("Firstname"));
    requested_columns.push_back(string("Lastname"));
    requested_columns.push_back(string("Middlename"));
    requested_columns.push_back(string("Assignee"));
    requested_columns.push_back(string("AsgNum"));
  }

  void load_fake_data() {

    describe_test(INDENT2, "Loading fake data for clustering...");

    const char * filename = "testdata/clustertest.csv";
    bool successful = fetch_records_from_txt(source, filename, requested_columns);

    if (not successful)
      exit(-1);
  }


  void create_cluster() {

    describe_test(INDENT2, "Creating clusters...");

    Attribute::register_class_names(get_column_names());
    Record * r = make_quuxalot_record();
    ClusterHead ch(r, 0.9953);
    RecordPList rl = get_record_list();
    cBlocking_Operation_By_Coauthors  blocker_coauthor = get_blocker_coathor();
    Cluster::set_reference_patent_tree_pointer( blocker_coauthor.get_patent_tree());
    //Cluster * c = new Cluster(ch, rl);
    //delete c;
  }

  void test_get_initial_prior() {

    describe_test(INDENT2, "Testing get_initial_prior");

    ClusterInfo::ClusterList rg;
    double prior = get_initial_prior(rg, false);

    std::cout << "prior: " << prior << std::endl;
  }

  void runTest() {
    load_fake_data();
    create_cluster();
    test_get_initial_prior();
  }
};


void
test_clusters() {

  ClusterInfoTest * cit = new ClusterInfoTest(std::string("initial test"));
  cit->runTest();
  delete cit;
}


#ifdef test_clusterinfo_STANDALONE
int
main(int UP(argc), char ** UP(argv)) {

  test_clusters();
  return 0;
}
#endif
