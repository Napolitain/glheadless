#include <glheadless/Context.h>

#ifdef _WIN32
#include "wgl/Implementation.h"
#endif


namespace glheadless {


Context Context::currentContext() {
    return Implementation::currentContext();
}


Context::Context()
: m_version(3, 2)
, m_profile(ContextProfile::CORE)
, m_debugContext(false)
, m_implementation(std::make_unique<Implementation>()) {
}


Context::Context(Context&& other) {
    *this = std::move(other);
}


Context::~Context() {
}


const PixelFormat& Context::pixelFormat() const {
    return m_pixelFormat;
}


void Context::setPixelFormat(const PixelFormat& pixelFormat) {
    m_pixelFormat = pixelFormat;
}


ContextProfile Context::profile() const {
    return m_profile;
}


void Context::setProfile(const ContextProfile profile) {
    m_profile = profile;
}


const Context::Version& Context::version() const {
    return m_version;
}


void Context::setVersion(int major, int minor) {
    m_version = { major, minor };
}


bool Context::debugContext() const {
    return m_debugContext;
}


void Context::setDebugContext(const bool debugContext) {
    m_debugContext = debugContext;
}


const std::map<int, int>& Context::attributes() const {
    return m_attributes;
}


void Context::setAttribute(int name, int value) {
    m_attributes[name] = value;
}


void Context::create() {
    m_implementation->create(this);
}


void Context::create(const Context& shared) {
    m_implementation->create(this, &shared);
}


void Context::makeCurrent() noexcept {
    m_implementation->makeCurrent(this);
}


void Context::doneCurrent() noexcept {
    m_implementation->doneCurrent(this);
}


Implementation* Context::implementation() {
    return m_implementation.get();
}


const Implementation* Context::implementation() const {
    return m_implementation.get();
}


Context& Context::operator=(Context&& other) {
    m_pixelFormat = other.m_pixelFormat;
    m_version = other.m_version;
    m_profile = other.m_profile;
    m_debugContext = other.m_debugContext;
    m_attributes = std::move(other.m_attributes);
    m_implementation = std::move(other.m_implementation);

    return *this;
}


}  // namespace glheadless
