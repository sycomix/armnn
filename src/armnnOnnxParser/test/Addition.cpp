//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include <boost/test/unit_test.hpp>
#include "armnnOnnxParser/IOnnxParser.hpp"
#include  "ParserPrototxtFixture.hpp"

BOOST_AUTO_TEST_SUITE(OnnxParser)

struct AddMainFixture : public armnnUtils::ParserPrototxtFixture<armnnOnnxParser::IOnnxParser>
{
    AddMainFixture(const std::string& dataType)
    {
        m_Prototext = R"(
                   ir_version: 3
                   producer_name:  "CNTK"
                   producer_version:  "2.5.1"
                   domain:  "ai.cntk"
                   model_version: 1
                   graph {
                     name:  "CNTKGraph"
                     input {
                        name: "Input0"
                        type {
                          tensor_type {
                            elem_type: )" + dataType + R"(
                            shape {
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 2
                              }
                              dim {
                                dim_value: 2
                              }
                            }
                          }
                        }
                      }
                      input {
                         name: "Input1"
                         type {
                           tensor_type {
                             elem_type: )" + dataType + R"(
                             shape {
                               dim {
                                 dim_value: 1
                               }
                               dim {
                                 dim_value: 1
                               }
                               dim {
                                 dim_value: 2
                               }
                               dim {
                                 dim_value: 2
                               }
                             }
                           }
                         }
                       }
                       node {
                            input: "Input0"
                            input: "Input1"
                            output: "Output"
                            name: "addition"
                            op_type: "Add"
                            doc_string: ""
                            domain: ""
                          }
                          output {
                              name: "Output"
                              type {
                                 tensor_type {
                                   elem_type: FLOAT
                                   shape {
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 2
                                       }
                                       dim {
                                           dim_value: 2
                                       }
                                   }
                                }
                            }
                        }
                    }
                   opset_import {
                      version: 7
                    })";
    }
};

struct AddValidFixture : AddMainFixture
{
    AddValidFixture() : AddMainFixture("FLOAT") {
        Setup();
    }
};

struct AddInvalidFixture : AddMainFixture
{
    AddInvalidFixture() : AddMainFixture("INT32") { }
};

struct AddValidBroadcastFixture : public armnnUtils::ParserPrototxtFixture<armnnOnnxParser::IOnnxParser>
{
    AddValidBroadcastFixture() {

        m_Prototext = R"(
                   ir_version: 3
                   producer_name:  "CNTK"
                   producer_version:  "2.5.1"
                   domain:  "ai.cntk"
                   model_version: 1
                   graph {
                     name:  "CNTKGraph"
                     input {
                        name: "Input0"
                        type {
                          tensor_type {
                            elem_type: FLOAT
                            shape {
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 4
                              }
                            }
                          }
                        }
                      }
                      input {
                         name: "Input1"
                         type {
                           tensor_type {
                             elem_type: FLOAT
                             shape {
                                 dim {
                                   dim_value: 4
                                 }
                             }
                           }
                         }
                       }
                       node {
                            input: "Input0"
                            input: "Input1"
                            output: "Output"
                            name: "addition"
                            op_type: "Add"
                            doc_string: ""
                            domain: ""
                          }
                          output {
                              name: "Output"
                              type {
                                 tensor_type {
                                   elem_type: FLOAT
                                   shape {
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 4
                                       }
                                   }
                                }
                            }
                        }
                    }
                   opset_import {
                      version: 7
                    })";
        Setup();
    }
};

struct AddInvalidBroadcastFixture : public armnnUtils::ParserPrototxtFixture<armnnOnnxParser::IOnnxParser>
{
    AddInvalidBroadcastFixture() {

        m_Prototext = R"(
                   ir_version: 3
                   producer_name:  "CNTK"
                   producer_version:  "2.5.1"
                   domain:  "ai.cntk"
                   model_version: 1
                   graph {
                     name:  "CNTKGraph"
                     input {
                        name: "Input0"
                        type {
                          tensor_type {
                            elem_type: FLOAT
                            shape {
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 1
                              }
                              dim {
                                dim_value: 3
                              }
                            }
                          }
                        }
                      }
                      input {
                         name: "Input1"
                         type {
                           tensor_type {
                             elem_type: FLOAT
                             shape {
                                 dim {
                                   dim_value: 4
                                 }
                             }
                           }
                         }
                       }
                       node {
                            input: "Input0"
                            input: "Input1"
                            output: "Output"
                            name: "addition"
                            op_type: "Add"
                            doc_string: ""
                            domain: ""
                          }
                          output {
                              name: "Output"
                              type {
                                 tensor_type {
                                   elem_type: FLOAT
                                   shape {
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 1
                                       }
                                       dim {
                                           dim_value: 4
                                       }
                                   }
                                }
                            }
                        }
                    }
                   opset_import {
                      version: 7
                    })";
    }
};

BOOST_FIXTURE_TEST_CASE(ValidAddTest, AddValidFixture)
{
    RunTest<4>({{"Input0", {1.0f, 2.0f, -3.0f, -4.0f}},
                {"Input1", {1.0f, 2.0f, 3.0, 4.0f}}}, {{"Output", {2.0, 4.0, 0, 0.0}}});
}

BOOST_FIXTURE_TEST_CASE(IncorrectDataTypeAdd, AddInvalidFixture)
{
   BOOST_CHECK_THROW(Setup(), armnn::ParseException);
}

BOOST_FIXTURE_TEST_CASE(InvalidBroadcastAdd, AddInvalidBroadcastFixture)
{
   BOOST_CHECK_THROW(Setup(), armnn::ParseException);
}

BOOST_FIXTURE_TEST_CASE(ValidBroadcastAdd, AddValidBroadcastFixture)
{
    RunTest<4>({{"Input0", {1.0f, 2.0f, -3.0f, -4.0f}},
                {"Input1", {1.0f, 2.0f, 3.0, 4.0f}}}, {{"Output", {2.0, 4.0, 0, 0.0}}});
}

BOOST_AUTO_TEST_SUITE_END()
