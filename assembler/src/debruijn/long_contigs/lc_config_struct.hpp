/*
 * lc_config_struct.hpp
 *
 *  Created on: Aug 16, 2011
 *      Author: Alexey.Gurevich
 */

#ifndef LC_CONFIG_STRUCT_HPP_
#define LC_CONFIG_STRUCT_HPP_

#include "../config_common.hpp"
#include "../config_struct.hpp"
#include <vector>

const char* const LC_CONFIG_FILENAME = "./src/debruijn/long_contigs/lc_config.info";

// struct for long_contigs subproject's configuration file
struct lc_config
{
	struct dataset
	{
		std::string graph_file;
	};

	struct basic_lib
	{
		size_t read_size;
		size_t insert_size;
	};

	struct rl_dataset
	{
		bool precounted;
	    std::string precounted_path;
		std::string first;
		std::string second;
	};

	struct real_lib
	{
		size_t read_size;
		size_t insert_size;

		rl_dataset ds;
	};

	struct etalon_lib
	{
		size_t read_size;
		size_t insert_size;
	};

	struct seed_selection
	{
	    double min_coverage;
	    bool   glue_seeds;
	};

	struct extension_selection
	{
		bool   use_weight_function_first;
		double weight_fun_threshold;
		double weight_threshold;

		bool use_delta_first;
		int  real_distance_dev;
		int  etalon_distance_dev;
	};

	struct loops_removal
	{
		size_t max_loops;
		bool full_loop_removal;
	};

	struct stop_criteria
	{
		bool all_seeds;
		double edge_coverage;
		double len_coverage;
	};

	struct filter_options
	{
		bool remove_duplicates_only;
		bool remove_overlaps;
	};

	bool from_file;

	//size_t real_libs_count;
	//size_t etalon_libs_count;

	bool write_seeds;
	bool write_overlaped_paths;
	bool write_paths;
	bool write_contigs;
	bool write_real_paired_info;
	bool cluster_paired_info;
	std::string paired_info_file_prefix;

	dataset ds;
	basic_lib bl;

	std::vector<real_lib> real_libs;
	std::vector<etalon_lib> etalon_libs;

	seed_selection ss;
	extension_selection es;
	loops_removal lr;
	stop_criteria sc;
	filter_options fo;
};


// specific load functions
void load(boost::property_tree::ptree const& pt, lc_config::rl_dataset& ds)
{
	load(pt, "precounted", ds.precounted);
	load(pt, "precounted_path", ds.precounted_path);
	load(pt, "first", ds.first);
	load(pt, "second", ds.second);
}

void load(boost::property_tree::ptree const& pt, lc_config::real_lib& rl)
{
	load(pt, "read_size", rl.read_size);
	load(pt, "insert_size", rl.insert_size);
	load(pt, cfg::get().dataset_name, rl.ds);
}

void load(boost::property_tree::ptree const& pt, lc_config::etalon_lib& el)
{
	load(pt, "insert_size", el.insert_size);
	load(pt, "read_size", el.read_size);
}

void load(boost::property_tree::ptree const& pt, lc_config::dataset& ds)
{
	load(pt, "graph_file", ds.graph_file);
}

void load(boost::property_tree::ptree const& pt, lc_config::basic_lib& bl)
{
	load(pt, "insert_size", bl.insert_size);
	load(pt, "read_size", bl.read_size);
}

void load(boost::property_tree::ptree const& pt, lc_config::seed_selection& ss)
{
	load(pt, "min_coverage", ss.min_coverage);
	load(pt, "glue_seeds", ss.glue_seeds);
}

void load(boost::property_tree::ptree const& pt, lc_config::extension_selection& es)
{
	load(pt, "use_weight_function_first", es.use_weight_function_first);
	load(pt, "weight_fun_threshold", es.weight_fun_threshold);
	load(pt, "weight_threshold", es.weight_threshold);
	load(pt, "use_delta_first", es.use_delta_first);
	load(pt, "real_distance_dev", es.real_distance_dev);
	load(pt, "etalon_distance_dev", es.etalon_distance_dev);
}

void load(boost::property_tree::ptree const& pt, lc_config::loops_removal& lr)
{
	load(pt, "max_loops", lr.max_loops);
	load(pt, "full_loop_removal", lr.full_loop_removal);
}

void load(boost::property_tree::ptree const& pt, lc_config::stop_criteria& sc)
{
	load(pt, "all_seeds", sc.all_seeds);
	load(pt, "edge_coverage", sc.edge_coverage);
	load(pt, "len_coverage", sc.len_coverage);
}

void load(boost::property_tree::ptree const& pt, lc_config::filter_options& fo)
{
	load(pt, "remove_overlaps", fo.remove_overlaps);
	load(pt, "remove_duplicates_only", fo.remove_duplicates_only);
}


// main debruijn config load function
void load(boost::property_tree::ptree const& pt, lc_config& lc_cfg)
{
	load(pt, "from_file", lc_cfg.from_file);
	//load(pt, "real_libs_count", cfg.real_libs_count);
	//load(pt, "etalon_libs_count", cfg.etalon_libs_count);

	load(pt, "write_seeds", lc_cfg.write_seeds);
	load(pt, "write_overlaped_paths", lc_cfg.write_overlaped_paths);
	load(pt, "write_paths", lc_cfg.write_paths);
	load(pt, "write_contigs", lc_cfg.write_contigs);
	load(pt, "write_real_paired_info", lc_cfg.write_real_paired_info);
	load(pt, "cluster_paired_info", lc_cfg.cluster_paired_info);
	load(pt, "paired_info_file_prefix", lc_cfg.paired_info_file_prefix);

	load(pt, cfg::get().dataset_name, lc_cfg.ds);
	load(pt, "bl", lc_cfg.bl);

	load(pt, "real_libs", lc_cfg.real_libs);
	load(pt, "etalon_libs", lc_cfg.etalon_libs);

	load(pt, "ss", lc_cfg.ss);
	load(pt, "es", lc_cfg.es);
	load(pt, "lr", lc_cfg.lr);
	load(pt, "sc", lc_cfg.sc);
	load(pt, "fo", lc_cfg.fo);
}


typedef config<lc_config> lc_cfg;

#endif /* CONFIG_STRUCT_HPP_ */
