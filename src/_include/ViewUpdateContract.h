#pragma once

#include <functional>
#include <memory>

template<typename UpdateResult>
class Presenter {
public:
	virtual ~Presenter() = default;
	virtual std::function<void(float)> getUpdateSource() = 0;

    void setUpdateReceiver(std::function<void(UpdateResult)> receiver) {
        onUpdateFinished = std::move(receiver);
    }

protected:
    std::function<void(UpdateResult)> onUpdateFinished;
};

template<typename UpdateResult, typename P, typename = std::enable_if<std::is_base_of<Presenter<UpdateResult>, P>::value>>
class View {
public:
    void setPresenter(std::shared_ptr<P> presenter) {
        this->requestUpdate = presenter->getUpdateSource();
        this->presenter = std::move(presenter);
    }

    virtual std::function<void(UpdateResult)> getUpdateReceiver() = 0;

protected:
    std::shared_ptr<P> presenter;
    std::function<void(float)> requestUpdate;
};

template<typename UpdateResult, typename P, typename = std::enable_if<std::is_base_of<Presenter<UpdateResult>, P>::value>>
void establishConnection(View<UpdateResult, P> *v, std::shared_ptr<P> &p) {
    v->setPresenter(p);
    p->setUpdateReceiver(v->getUpdateReceiver());
}