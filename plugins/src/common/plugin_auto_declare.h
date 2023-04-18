//
// Created by nrsl on 23-4-15.
//

#ifndef POINT_DETECTION_PLUGIN_AUTO_DECLARE_H
#define POINT_DETECTION_PLUGIN_AUTO_DECLARE_H

#include <cstring>
#include <cassert>

#include <sstream>
#include <vector>
#include <iostream>

#include <NvInferRuntime.h>

namespace {
#define TRT__CAT(a, b) a##b
#define TRT_CAT(a, b) TRT__CAT(a,b)
#define TRT__STR(a) #a
#define TRT_STR(a) TRT__STR(a)
#define TRT_FWD(...) __VA_ARGS__

#define TENSORRT_PLUGIN_GET_0(x) x
#define TENSORRT_PLUGIN_GET_1(x, ...) TENSORRT_PLUGIN_GET_0(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_2(x, ...) TENSORRT_PLUGIN_GET_1(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_3(x, ...) TENSORRT_PLUGIN_GET_2(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_4(x, ...) TENSORRT_PLUGIN_GET_3(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_5(x, ...) TENSORRT_PLUGIN_GET_4(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_6(x, ...) TENSORRT_PLUGIN_GET_5(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_7(x, ...) TENSORRT_PLUGIN_GET_6(__VA_ARGS__)
#define TENSORRT_PLUGIN_GET_8(x, ...) TENSORRT_PLUGIN_GET_7(__VA_ARGS__)

#define TENSORRT_PLUGIN_Dim1(_1)       Dimension(_1)
#define TENSORRT_PLUGIN_Dim2(_1, _2)    TENSORRT_PLUGIN_Dim1(_1) Dimension(_2)
#define TENSORRT_PLUGIN_Dim3(_1, _2, _3) TENSORRT_PLUGIN_Dim2(_1,_2) Dimension(_3)
#define TENSORRT_PLUGIN_Dim4(_1, _2, _3, _4) TENSORRT_PLUGIN_Dim3(_1,_2,_3) Dimension(_4)
#define TENSORRT_PLUGIN_Dim5(_1, _2, _3, _4, _5) TENSORRT_DIM4(_1,_2,_3,_4) Dimension(_5)
#define TENSORRT_PLUGIN__Setting(...) (__VA_ARGS__)
#define TENSORRT_PLUGIN_SETTING  TRT_CAT(TENSORRT_PLUGIN__,TENSORRT_PLUGIN)

#define TENSORRT_PLUGIN___Name(n) n
#define TENSORRT_PLUGIN__NAME(n, ...) TRT_CAT(TENSORRT_PLUGIN___,n)
#define TENSORRT_PLUGIN_SETTING_NAME TRT_FWD(TENSORRT_PLUGIN__NAME TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___Version(v) v
#define TENSORRT_PLUGIN__VERSION(_, v, ...) TRT_CAT(TENSORRT_PLUGIN___,v)
#define TENSORRT_PLUGIN_SETTING_VERSION TRT_FWD(TENSORRT_PLUGIN__VERSION TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___ATTR(...) __VA_ARGS__
#define TENSORRT_PLUGIN__ATTR(name, version, define, inputs, outputs, workspace, attributes) TENSORRT_PLUGIN___ATTR attributes
#define TENSORRT_PLUGIN_SETTING_ATTR TRT_FWD(TENSORRT_PLUGIN__ATTR TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___INPUT(...) __VA_ARGS__
#define TENSORRT_PLUGIN__INPUT(name, version, define, inputs, outputs, workspace, attributes) TENSORRT_PLUGIN___INPUT inputs
#define TENSORRT_PLUGIN_SETTING_INPUT TRT_FWD(TENSORRT_PLUGIN__INPUT TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___OUTPUT(...) __VA_ARGS__
#define TENSORRT_PLUGIN__OUTPUT(name, version, define, inputs, outputs, workspace, attributes) TENSORRT_PLUGIN___OUTPUT outputs
#define TENSORRT_PLUGIN_SETTING_OUTPUT TRT_FWD(TENSORRT_PLUGIN__OUTPUT TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___WORKSPACE(...) __VA_ARGS__
#define TENSORRT_PLUGIN__WORKSPACE(name, version, define, inputs, outputs, workspace, attributes) TENSORRT_PLUGIN___WORKSPACE workspace
#define TENSORRT_PLUGIN_SETTING_WORKSPACE TRT_FWD(TENSORRT_PLUGIN__WORKSPACE TENSORRT_PLUGIN_SETTING)

#define TENSORRT_PLUGIN___DEFINE(...) __VA_ARGS__
#define TENSORRT_PLUGIN__DEFINE(name, version, define, inputs, outputs, workspace, attributes) TENSORRT_PLUGIN___DEFINE define
#define TENSORRT_PLUGIN_SETTING_DEFINE TRT_FWD(TENSORRT_PLUGIN__DEFINE TENSORRT_PLUGIN_SETTING)

#ifdef TENSORRT_PLUGIN_DEBUG
#define TrTPrintf(...) fprintf(stderr,"[%s]: ",__FUNCTION__); fprintf(stderr,__VA_ARGS__)
#elif
#define TrTPrintf(...)
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define TENSORRT_PLUGIN_NAME TRT_CAT(TENSORRT_PLUGIN_SETTING_NAME,Plugin)
#define TENSORRT_PLUGIN_CREATOR_NAME TRT_CAT(TENSORRT_PLUGIN_SETTING_NAME,PluginCreator)
#define TENSORRT_PLUGIN_USER_INTERFACE TRT_CAT(TENSORRT_PLUGIN_SETTING_NAME, User)
struct TENSORRT_PLUGIN_USER_INTERFACE;
namespace nvinfer1::plugin {
struct Dummy {
};

template<typename T, typename = void>
struct as_base_if_it_is_complete_type : Dummy {
};

template<typename T>
struct as_base_if_it_is_complete_type<T, decltype(void(sizeof(T)))> : T {
};

inline auto TryExpr(int32_t t, nvinfer1::IExprBuilder &exprBuilder) {
    return exprBuilder.constant(t);
}

inline auto TryExpr(const IDimensionExpr *const &t, nvinfer1::IExprBuilder &exprBuilder) {
    return t;
}


template<typename C>
inline constexpr PluginFieldType type2field() {
    if constexpr(std::is_same_v<double, C>) {
        return PluginFieldType::kFLOAT64;
    } else if constexpr(std::is_same_v<float, C>) {
        return PluginFieldType::kFLOAT32;
    } else if constexpr(std::is_same_v<int, C> or std::is_same_v<unsigned int, C>) {
        return PluginFieldType::kINT32;
    } else if constexpr(std::is_same_v<unsigned char, C>) {
        return PluginFieldType::kINT8;
    } else if constexpr(std::is_same_v<char, C>) {
        return PluginFieldType::kCHAR;
    } else {
        assert(false);
        return PluginFieldType::kUNKNOWN;
    }
}

template<typename C>
inline constexpr DataType type2data() {
    if constexpr(std::is_same_v<float, C>) {
        return DataType::kFLOAT;
    } else if constexpr(std::is_same_v<int, C> or std::is_same_v<unsigned int, C>) {
        return DataType::kINT32;
    } else if constexpr(std::is_same_v<char, C> or std::is_same_v<unsigned char, C>) {
        return DataType::kINT8;
    } else if constexpr(std::is_same_v<bool, C>) {
        return DataType::kBOOL;
    } else {
        assert(false);
        return DataType::kFLOAT;
    }
}

inline constexpr const char *data2str(const DataType &data) {
    switch (data) {
        case DataType::kFLOAT:
            return "float";
        case DataType::kHALF:
            return "half";
        case DataType::kINT8:
            return "int8";
        case DataType::kINT32:
            return "int32";
        case DataType::kBOOL:
            return "bool";
        default:
            return "unknown";
    }
}

template<typename T>
struct TypeInfo {
    using type = T;
    static constexpr int len = 1;
    static constexpr auto field_type = type2field<std::remove_cv_t<T>>();
    static constexpr auto data_type = type2data<std::remove_cv_t<T>>();

    static void DeepCopy(T &val, const T &data) {
        val = data;
        #ifdef TENSORRT_PLUGIN_DEBUG
        std::stringstream ss;
        ss << val << " = " << data;
        TrTPrintf("%s\n", ss.str().c_str());
        #endif
    }

    static void ReadBuffer(T &val, const void *const data) {
        val = static_cast<T const *>(data)[0];
        #ifdef TENSORRT_PLUGIN_DEBUG
        std::stringstream ss;
        ss << val << " = " << static_cast<T const *>(data)[0];
        TrTPrintf("%s\n", ss.str().c_str());
        #endif
    }

    template<typename buffer_type>
    static void WriteBuffer(const T &val, buffer_type *&data) {
        #ifdef TENSORRT_PLUGIN_DEBUG
        std::stringstream ss;
        ss << reinterpret_cast<T *>(data)[0] << " = " << val;
        TrTPrintf("%s\n", ss.str().c_str());
        #endif
        reinterpret_cast<T *>(data)[0] = val;
        data = reinterpret_cast<buffer_type *>(reinterpret_cast<T *>(data) + 1);
    }
};

template<typename T, int N>
struct TypeInfo<T[N]> {
    using type = T;
    using array_type = T[N];
    static constexpr int len = N;
    static constexpr auto field_type = type2field<std::remove_cv_t<T>>();
    static constexpr auto data_type = type2data<std::remove_cv_t<T>>();

    static void DeepCopy(array_type &val, const array_type &data) {
        for (int i = 0; i < N; ++i) {
            TypeInfo<T>::DeepCopy(val[i], data[i]);
        }
    }

    static void ReadBuffer(array_type &val, const void *const data) {
        auto *ptr = static_cast<T const *>(data);
        for (int i = 0; i < N; ++i) {
            TypeInfo<T>::ReadBuffer(val[i], &ptr[i]);
        }
    }

    template<typename buffer_type>
    static void WriteBuffer(const array_type &val, buffer_type *&data) {
        for (int i = 0; i < N; ++i) {
            TypeInfo<T>::WriteBuffer(val[i], data);
        }
    }
};

inline size_t SizeAlign256(size_t size) {
    constexpr size_t align = 256;
    return size + (size % align ? align - (size % align) : 0);
}

template<typename T>
inline T *GetOneWorkspace(void *const workspace, size_t size, size_t &offset) {
    auto buffer = reinterpret_cast<size_t>( workspace) + offset;
    offset += SizeAlign256(size);
    return reinterpret_cast<T *>( buffer);
}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nvinfer1::plugin {
class TENSORRT_PLUGIN_NAME
        : public nvinfer1::IPluginV2DynamicExt,
          public as_base_if_it_is_complete_type<TENSORRT_PLUGIN_USER_INTERFACE> {
    struct Type {
        #define Attribute(t, n, ...)  using n=t;
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute
        #define Workspace(t, n, ...)  using n=t;
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Workspace
        #define Input(t, n, ...)  using n=t;
        TENSORRT_PLUGIN_SETTING_INPUT
        #undef Input
        #define Output(t, n, ...)  using n=t;
        TENSORRT_PLUGIN_SETTING_OUTPUT
        #undef Output
    };

    struct {
        #define Define(n, ...) int32_t n{0};
        TENSORRT_PLUGIN_SETTING_DEFINE
        #undef Define
    } def;
    struct {
        #define Attribute(t, n, ...)  Type::n n=__VA_ARGS__;
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute
    } attr;
    struct {
        struct {
            #define Workspace(t, n, ...)  size_t n{0};
            TENSORRT_PLUGIN_SETTING_WORKSPACE
            #undef Workspace
        } size;
        #define Workspace(t, n, ...)  t* n{nullptr};
        TENSORRT_PLUGIN_SETTING_WORKSPACE;
        #undef Workspace
    } ws;
    struct {
        #define Input(t, n, ...) const t * n{nullptr};
        TENSORRT_PLUGIN_SETTING_INPUT
        #undef Input
    } input;
    struct {
        #define Output(t, n, ...) t * n{nullptr};
        TENSORRT_PLUGIN_SETTING_OUTPUT
        #undef Output
    } output;

    std::string namespace_;

    TENSORRT_PLUGIN_NAME() = delete;

 private:
    auto GetWorkSpaceSizes(nvinfer1::PluginTensorDesc const *inputs, nvinfer1::PluginTensorDesc const *outputs) const {
        decltype(ws.size) sizes;
        #define Input(nin, ndim, ...)  inputs[nin].dims.d[ndim]
        #define Output(nin, ndim, ...)  outputs[nin].dims.d[ndim]
        #define Attr(name, ...)  attr.name
        #define Dimension(...) * __VA_ARGS__

        #define Define(name, ...)                                                                                       \
        const auto name=__VA_ARGS__;
        TENSORRT_PLUGIN_SETTING_DEFINE

        #define Workspace(t, n, ...)                                                                                    \
        sizes.n = sizeof(t) TRT_CAT(TENSORRT_PLUGIN_,__VA_ARGS__);                                                      \
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Input
        #undef Output
        #undef Attr
        #undef Dimension
        #undef Define
        #undef Workspace

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #ifdef TENSORRT_PLUGIN_DEBUG
        #define Dimension(...) <<__VA_ARGS__<<" x "
        #define Workspace(t, n, ...)                                                                                    \
        {                                                                                                               \
            std::stringstream ss;                                                                                       \
            ss TRT_CAT(TENSORRT_PLUGIN_,__VA_ARGS__) << sizeof(t);                                                      \
            TrTPrintf("%s = %s\n", #n, ss.str().c_str());                                                \
        }
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Dimension
        #undef Workspace
        #endif
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        return sizes;
    }

    inline void SetIOPointer(void const *const *inputs, void *const *outputs) {
        int ni = 0;
        #define Input(t, n, ...)                                                                                        \
        input.n = static_cast<const t* >(inputs[ni++]);                                                                 \
        TrTPrintf("%p(%s)\n", input.n,#n);
        TENSORRT_PLUGIN_SETTING_INPUT
        #undef Input

        int no = 0;
        #define Output(t, n, ...)                                                                                       \
        output.n = static_cast<t* >(outputs[no++]);                                                                     \
        TrTPrintf("%p(%s)\n", output.n,#n);
        TENSORRT_PLUGIN_SETTING_OUTPUT
        #undef Output
    }

    inline void SetWorkspacePtr(void *workspace) {
        size_t offset = 0;
        #define Workspace(type, name, ...)                                                                              \
        ws.name = GetOneWorkspace<type>(workspace, ws.size.name, offset);                                               \
        TrTPrintf("%p(%s)\n", ws.name, #name);
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Workspace
    }

    inline void SetDefine(PluginTensorDesc const *inputs, PluginTensorDesc const *outputs) {
        #define Attr(name, ...)  attr.name
        #define Output(nin, ndim, ...)  int(0)
        #define Input(nin, ndim, ...)  inputs[nin].dims.d[ndim]
        #define Define(name, ...)                                                                                       \
        auto name = def.name =__VA_ARGS__;
        TENSORRT_PLUGIN_SETTING_DEFINE
        #undef Output
        #undef Input
        #undef Define
    }

    inline void SetWorkSpaceSize(nvinfer1::PluginTensorDesc const *inputs, nvinfer1::PluginTensorDesc const *outputs) {
        ws.size = GetWorkSpaceSizes(inputs, outputs);
        #define Workspace(t, n, ...)                                                                                    \
        TrTPrintf("%s = %lu\n", #n, ws.size.n );
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Workspace
    }

    void InitAllShapeAndPointer(PluginTensorDesc const *inputDesc,
                                PluginTensorDesc const *outputDesc,
                                void const *const *inputs,
                                void *const *outputs,
                                void *workspace) {
        SetDefine(inputDesc, outputDesc);
        SetWorkSpaceSize(inputDesc, outputDesc);
        SetIOPointer(inputs, outputs);
        SetWorkspacePtr(workspace);
    }

 public:

    void serialize(void *buffer) const noexcept override {
        assert(buffer != nullptr);
        auto *ptr = reinterpret_cast<uint8_t *>(buffer);
        auto *begin = ptr;
        #define Attribute(type, name, ...)                                                                              \
        TypeInfo<decltype(attr.name)>::WriteBuffer(attr.name, ptr);
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute
        TrTPrintf("%lu = %lu + %lu ?\n", (size_t) ptr, (size_t) begin, getSerializationSize());
        assert(ptr == begin + getSerializationSize());
    }

    void setPluginNamespace(char const *pluginNamespace) noexcept override {
        assert(pluginNamespace != nullptr);
        namespace_ = pluginNamespace;
        TrTPrintf("%s\n", namespace_.c_str());
    }

    [[nodiscard]] size_t getSerializationSize() const noexcept override {
        #define Attribute(type, name, ...) + sizeof(attr.name)
        constexpr size_t serialization_size{0 TENSORRT_PLUGIN_SETTING_ATTR};
        #undef Attribute
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::stringstream ss;
        #ifdef TENSORRT_PLUGIN_DEBUG
        #define Attribute(type, name, ...)                                                                              \
        << " + " << sizeof(attr.name) <<  "(" #name ")"
        ss TENSORRT_PLUGIN_SETTING_ATTR;
        #undef Attribute
        TrTPrintf("%zu =%s\n", serialization_size, ss.str().c_str());
        #endif
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        return serialization_size;
    }

    static int32_t getNbInputs() noexcept {
        #define Input(type, name, ...) (+1)
        constexpr int32_t n = (0 + TENSORRT_PLUGIN_SETTING_INPUT);
        TrTPrintf("%d\n", n);
        #undef Input
        return n;
    }

    [[nodiscard]] int32_t getNbOutputs() const noexcept override {
        #define Output(type, name, ...) (+1)
        constexpr int32_t n = (0 + TENSORRT_PLUGIN_SETTING_OUTPUT);
        #undef Output
        TrTPrintf("%d\n", n);
        return n;
    }

    [[nodiscard]] char const *getPluginNamespace() const noexcept override {
        TrTPrintf("%s\n", namespace_.c_str());
        return namespace_.c_str();
    }

    [[nodiscard]] char const *getPluginVersion() const noexcept override {
        TrTPrintf("%s\n", TENSORRT_PLUGIN_SETTING_VERSION);
        return TENSORRT_PLUGIN_SETTING_VERSION;
    }

    [[nodiscard]] char const *getPluginType() const noexcept override {
        TrTPrintf("%s\n", TRT_STR(TENSORRT_PLUGIN_SETTING_NAME));
        return TRT_STR(TENSORRT_PLUGIN_SETTING_NAME);
    }

    void destroy() noexcept override {
        delete this;
    }

    void terminate() noexcept override;

    int32_t initialize() noexcept override;

 public:

    TENSORRT_PLUGIN_NAME(void const *data, size_t length) {
        assert(data != nullptr);
        auto const *d = reinterpret_cast<uint8_t const *>(data);
        auto const *a = d;

        #define Attribute(t, n, ...)                                                                                    \
        TypeInfo<decltype(attr.n)>::ReadBuffer(attr.n, d);                                                              \
        d+=sizeof(attr.n);
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute


        #define Attribute(t, n, ...) std::cerr<<"["<<__FUNCTION__<< "]: "<< attr.n<<"("<<#n<<")"<<std::endl;
        TrTPrintf("deserialization\n");
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute

        assert(d == a + length);
    }

    TENSORRT_PLUGIN_NAME(
            #define Attribute(t, n, ...) ,const Type::n &_##n
            void *TENSORRT_PLUGIN_SETTING_ATTR) {
        #undef Attribute
        #define Attribute(t, n, ...)  TypeInfo<decltype(attr.n)>::DeepCopy(attr.n,_##n);
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute
    }

    [[nodiscard]] nvinfer1::IPluginV2DynamicExt *clone() const noexcept override {
        #define Attribute(t, n, ...) , attr.n
        auto *plugin = new TENSORRT_PLUGIN_NAME(nullptr TENSORRT_PLUGIN_SETTING_ATTR);
        #undef Attribute
        plugin->setPluginNamespace(namespace_.c_str());
        return plugin;
    }

    nvinfer1::DimsExprs getOutputDimensions(int32_t outputIndex, nvinfer1::DimsExprs const *inputs, int32_t nbInputs,
                                            nvinfer1::IExprBuilder &exprBuilder) noexcept override {
        assert(0 <= outputIndex && outputIndex < this->getNbOutputs());
        #define Attr(name, ...)  attr.name
        #define Output(nin, ndim, ...)  int(0)
        #define Input(nin, ndim, ...)  inputs[nin].d[ndim]->getConstantValue()
        #define Define(name, ...)                                                                                       \
        const auto name = __VA_ARGS__;
        TENSORRT_PLUGIN_SETTING_DEFINE
        #undef Output
        #undef Input
        #undef Define

        int n_out = 0;
        nvinfer1::DimsExprs dim{};

        #define Dimension(...)  dim.d[n_dim++]=TryExpr(__VA_ARGS__,exprBuilder);
        #define Output(t, n, ...) \
        if ( outputIndex == n_out++) {                                                                                  \
            int n_dim=0;                                                                                                \
            TRT_CAT(TENSORRT_PLUGIN_,__VA_ARGS__)                                                                       \
            dim.nbDims = n_dim;                                                                                         \
        } else
        TENSORRT_PLUGIN_SETTING_OUTPUT { assert(false); }
        #undef Dimension
        #undef Const
        #undef Output

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #ifdef TENSORRT_PLUGIN_DEBUG
        #define Input(nin, ndim, ...)  inputs[nin].d[ndim]
        #define Dimension(...)  <<__VA_ARGS__<<","
        #define Output(t, n, ...)                                                                                       \
        {                                                                                                               \
            std::stringstream ss;                                                                                       \
            ss TRT_CAT(TENSORRT_PLUGIN_,__VA_ARGS__);                                                                   \
            std::string s=ss.str();                                                                                     \
            s.pop_back();                                                                                               \
            TrTPrintf("%s %s[%s]\n",#n,#t,s.c_str());                                                                   \
        }
        TENSORRT_PLUGIN_SETTING_OUTPUT
        #undef Dimension
        #undef Input
        #undef Output
        #undef Attr
        #endif
        return dim;
    }

    nvinfer1::DataType getOutputDataType(
            int32_t index, nvinfer1::DataType const *inputTypes, int32_t nbInputs) const noexcept override {
        assert(inputTypes != nullptr);
        int i = 0;
        #define Output(t, n, ...)                                                                                       \
        if (index == i++) {                                                                                             \
            TrTPrintf("%s %s\n", #n, data2str(TypeInfo<int>::data_type));                                               \
            return TypeInfo<int>::data_type;                                                                            \
        } else
        TENSORRT_PLUGIN_SETTING_OUTPUT {
            assert(false);
            return nvinfer1::DataType{};
        }
        #undef Output
    }

    bool supportsFormatCombination(
            int32_t pos, nvinfer1::PluginTensorDesc const *inOut, int32_t nbInputs,
            int32_t nbOutputs) noexcept override {

        assert(inOut != nullptr);
        assert(nbInputs == getNbInputs());
        assert(nbOutputs == getNbOutputs());

        int i = 0;
        PluginTensorDesc const &io = inOut[pos];

        #define IF_ELSE(t, n, ...)                                                                                      \
        if (pos == i++) {                                                                                               \
            TrTPrintf("%s, %s\n",#n,data2str(TypeInfo<t>::data_type));                                                  \
            return (TypeInfo<t>::data_type == io.type) && (io.format == TensorFormat::kLINEAR);}                        \
        else
        #define Input(...) IF_ELSE(__VA_ARGS__)
        #define Output(...) IF_ELSE(__VA_ARGS__)
        TENSORRT_PLUGIN_SETTING_INPUT TENSORRT_PLUGIN_SETTING_OUTPUT {
            assert(false);
            return false;
        }
        #undef Input
        #undef Output
    }

    void configurePlugin(nvinfer1::DynamicPluginTensorDesc const *in, int32_t nbInputs,
                         nvinfer1::DynamicPluginTensorDesc const *out, int32_t nbOutputs) noexcept override {
        assert(in != nullptr);
        assert(out != nullptr);
        assert(nbInputs == getNbInputs());
        assert(nbOutputs == getNbOutputs());
    }

    size_t getWorkspaceSize(nvinfer1::PluginTensorDesc const *inputs, int32_t nbInputs,
                            nvinfer1::PluginTensorDesc const *outputs, int32_t nbOutputs) const noexcept override {
        auto sizes = GetWorkSpaceSizes(inputs, outputs);
        size_t total = 0;
        #define Workspace(data_type, data_name, ...)                                                                    \
        total += SizeAlign256(sizes.data_name);                                                                       \
        TrTPrintf("%zu(total)\n", total);
        TENSORRT_PLUGIN_SETTING_WORKSPACE
        #undef Workspace
        return total;
    };

    int32_t enqueue(nvinfer1::PluginTensorDesc const *inputDesc, nvinfer1::PluginTensorDesc const *outputDesc,
                    void const *const *inputs, void *const *outputs, void *workspace,
                    cudaStream_t stream) noexcept override {
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #ifdef TENSORRT_PLUGIN_DEBUG
        TrTPrintf("enqueue\n");
        int n_in = 0;
        #define PRINT(desc, t, n, ...)                                                                                  \
        {                                                                                                               \
            std::stringstream ss;                                                                                       \
            for (int i = 0; i < desc[n_in].dims.nbDims; i++) {                                                          \
                ss<<desc[n_in].dims.d[i]<<(i == desc[n_in].dims.nbDims - 1 ? "" : ",");                                 \
            }                                                                                                           \
            TrTPrintf("%s %s[%s] format: %d\n",                                                                         \
                #n, data2str(desc[n_in].type),ss.str().c_str(),(int)desc[n_in].format);                                 \
        }
        #define Input(t, n, ...) PRINT(inputDesc,t,n)
        #define Output(t, n, ...) PRINT(outputDesc,t,n)
        TENSORRT_PLUGIN_SETTING_INPUT
        TENSORRT_PLUGIN_SETTING_OUTPUT
        #undef Input
        #undef Output
        #undef PRINT
        #endif
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        InitAllShapeAndPointer(inputDesc, outputDesc, inputs, outputs, workspace);
        return enqueue(stream);
    }

    int32_t enqueue(cudaStream_t stream) noexcept;

    friend class TENSORRT_PLUGIN_CREATOR_NAME;
};

class TENSORRT_PLUGIN_CREATOR_NAME : public nvinfer1::IPluginCreator {
    decltype(TENSORRT_PLUGIN_NAME::attr) attr;

 public:
    TENSORRT_PLUGIN_CREATOR_NAME() {
        plugin_attributes_.clear();
        #define Attribute(type, name, ...)                                                                              \
        plugin_attributes_.emplace_back(                                                                                \
            PluginField(TRT_STR(name), nullptr,                                                                         \
            TypeInfo<decltype(attr.name)>::field_type,                                                                  \
            TypeInfo<decltype(attr.name)>::len)                                                                         \
        );
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute
        field_collection_.nbFields = plugin_attributes_.size();
        field_collection_.fields = plugin_attributes_.data();
    }

    nvinfer1::IPluginV2 *createPlugin(char const *name, nvinfer1::PluginFieldCollection const *fc) noexcept override {
        assert(fc != nullptr);

        #define Attribute(type, data_name, ...)                                                                         \
        decltype(attr.data_name) data_name;
        TENSORRT_PLUGIN_SETTING_ATTR
        #undef Attribute

        int32_t num_fields = fc->nbFields;
        for (auto i = 0; i < num_fields; ++i) {
            auto &field = fc->fields[i];
            #define Attribute(type, data_name, ...)                                                                     \
            if(!strcmp(field.name, #data_name)){                                                                        \
                TypeInfo<decltype(data_name)>::ReadBuffer(data_name, field.data);                                       \
            }else
            TENSORRT_PLUGIN_SETTING_ATTR {
                assert(0);
            }
            #undef Attribute
        }
        #define Attribute(type, name, ...)  , name
        IPluginV2 *plugin = new TENSORRT_PLUGIN_NAME(nullptr TENSORRT_PLUGIN_SETTING_ATTR);
        #undef Attribute
        return plugin;
    }

    [[nodiscard]] char const *getPluginName() const noexcept override {
        return TRT_STR(TENSORRT_PLUGIN_SETTING_NAME);
    }

    [[nodiscard]] char const *getPluginVersion() const noexcept override {
        return TENSORRT_PLUGIN_SETTING_VERSION;
    }

    nvinfer1::PluginFieldCollection const *getFieldNames() noexcept override {
        return &field_collection_;
    }

    nvinfer1::IPluginV2 *deserializePlugin(char const *name, void const *data, size_t length) noexcept override {
        return new TENSORRT_PLUGIN_NAME(data, length);
    }

    void setPluginNamespace(char const *pluginNamespace) noexcept override {
        assert(pluginNamespace != nullptr);
        namespace_ = pluginNamespace;
    }

    [[nodiscard]] char const *getPluginNamespace() const noexcept override {
        return namespace_.c_str();
    }

 private:
    static nvinfer1::PluginFieldCollection field_collection_;
    static std::vector<nvinfer1::PluginField> plugin_attributes_;
    std::string namespace_;
};

PluginFieldCollection TENSORRT_PLUGIN_CREATOR_NAME::field_collection_{};
std::vector<PluginField> TENSORRT_PLUGIN_CREATOR_NAME::plugin_attributes_;
REGISTER_TENSORRT_PLUGIN(TENSORRT_PLUGIN_CREATOR_NAME);
}

#endif //POINT_DETECTION_PLUGIN_AUTO_DECLARE_H
