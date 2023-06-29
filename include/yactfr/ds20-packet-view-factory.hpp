#pragma once

#include <memory>
#include <boost/noncopyable.hpp>
#include <string>

#include <stdint.h>
#include "data-src-factory.hpp"
#include "aliases.hpp"

namespace yactfr {
namespace internal {

class DS20PacketViewFactoryImpl;

}

class DS20PacketViewFactory final :
    public DataSourceFactory,
    boost::noncopyable
{
public:

public:
    explicit DS20PacketViewFactory(uint8_t *buffer, size_t bufferSize);

private:
    DataSource::UP _createDataSource() override;

private:
    /*
     * Shared because memory mapped file views also keep a reference to
     * keep the file descriptor opened.
     */
    std::shared_ptr<internal::DS20PacketViewFactoryImpl> _pimpl;
};

} // namespace yactfr
