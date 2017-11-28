/*
 *   All basic functions and primary connections to node.js
 */

#include <string.h>
#include "node-fann.h"

void NNet::PrototypeInit(Local<FunctionTemplate> t)
{
  t->InstanceTemplate()->SetInternalFieldCount(1);
  t->SetClassName(Nan::New<String>("FANN").ToLocalChecked());

  Nan::SetPrototypeMethod(t, "standard", NewStandard);
  Nan::SetPrototypeMethod(t, "sparse", NewSparse);
  Nan::SetPrototypeMethod(t, "shortcut", NewShortcut);
  Nan::SetPrototypeMethod(t, "fromFile", NewFromFile);
  
  
  Nan::SetPrototypeMethod(t, "train", Train);
  Nan::SetPrototypeMethod(t, "cascadetrain", CascadeTrain);
  Nan::SetPrototypeMethod(t, "train_once", TrainOnce);
  Nan::SetPrototypeMethod(t, "run", Run);
  Nan::SetPrototypeMethod(t, "save", SaveToFile);

  Nan::SetPrototypeMethod(t, "activation_function", ActivationFunction);
  Nan::SetPrototypeMethod(t, "activation_function_hidden", ActivationFunctionHidden);
  Nan::SetPrototypeMethod(t, "activation_function_output", ActivationFunctionOutput);
  Nan::SetPrototypeMethod(t, "get_num_input", GetNumInput);
  Nan::SetPrototypeMethod(t, "get_MSE", GetMse);
  Nan::SetPrototypeMethod(t, "get_num_output", GetNumOutput);
  Nan::SetPrototypeMethod(t, "get_total_neurons", GetTotalNeurons);
  Nan::SetPrototypeMethod(t, "get_total_connections", GetTotalConnections);
  Nan::SetPrototypeMethod(t, "get_network_type", GetNetworkType);
  Nan::SetPrototypeMethod(t, "get_connection_rate", GetConnectionRate);

  // use net->layers instead ?
  Nan::SetPrototypeMethod(t, "get_num_layers", GetNumLayers);
  Nan::SetPrototypeMethod(t, "get_layer_array", GetLayerArray);

  Nan::SetPrototypeMethod(t, "get_bias_array", GetBiasArray);
  Nan::SetPrototypeMethod(t, "get_weight_array", GetWeights);
  Nan::SetPrototypeMethod(t, "set_weight_array", SetWeights);
  Nan::SetPrototypeMethod(t, "get_weight", GetWeights);
  Nan::SetPrototypeMethod(t, "set_weight", SetWeights);

  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("training_algorithm").ToLocalChecked(), GetTrainingAlgorithm, SetTrainingAlgorithm);
  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("train_error_function").ToLocalChecked(), GetErrorFunction, SetErrorFunction);
  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("train_stop_function").ToLocalChecked(), GetErrorStop, SetErrorStop);
  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("learning_rate").ToLocalChecked(), GetLearningRate, SetLearningRate);
  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("learning_momentum").ToLocalChecked(), GetLearningMomentum, SetLearningMomentum);
  Nan::SetAccessor(t->InstanceTemplate(), Nan::New("layers").ToLocalChecked(), GetLayerArray, 0);

  /*
  t->InstanceTemplate()->SetAccessor(Nan::New<String>("training_algorithm").ToLocalChecked(), GetTrainingAlgorithm, SetTrainingAlgorithm);
  t->InstanceTemplate()->SetAccessor(Nan::New<String>("learning_rate").ToLocalChecked(), GetLearningRate, SetLearningRate);
  t->InstanceTemplate()->SetAccessor(Nan::New<String>("learning_momentum").ToLocalChecked(), GetLearningMomentum, SetLearningMomentum);
  t->InstanceTemplate()->SetAccessor(Nan::New<String>("layers").ToLocalChecked(), GetLayerArray);
  */
}

  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  NAN_METHOD(NNet::New) {
    if (info.IsConstructCall()) {
      NNet *obj = new NNet();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      //const int argc = 0;
      //v8::Local<v8::Value> argv[] = {};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, 0, NULL).ToLocalChecked());
    }
  }

void NNet::Initialize(Handle<Object> target)
{
  Nan::HandleScope scope;
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  PrototypeInit(tpl);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("net").ToLocalChecked(),
      Nan::GetFunction(tpl).ToLocalChecked());
  
  Nan::SetMethod(target, "get_all_training_algorithms", GetTrainingAlgorithmList);
  Nan::SetMethod(target, "get_all_activation_functions", GetActivationFunctionList);
  Nan::SetMethod(target, "get_all_network_types", GetNetworkTypeList);
  Nan::SetMethod(target, "get_all_stop_functions", GetStopFuncList);
  Nan::SetMethod(target, "get_all_error_functions", GetErrorFuncList);
}

extern "C" void init (Handle<Object> target)
{
  Nan::HandleScope scope;
  NNet::Initialize(target);
}

#ifdef NODE_MODULE
NODE_MODULE(fann, init)
#endif

