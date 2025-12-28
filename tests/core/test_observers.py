"""
Tests for observer pattern implementation
"""
import pytest
from autosar_configurator.core.model.observers import Observer, Subject


class TestObserver(Observer):
    """Mock observer for testing"""

    def __init__(self):
        self.events = []

    def handle_update(self, event: str, data=None):
        self.events.append({'event': event, 'data': data})


class TestSubject:
    """Tests for Subject class"""

    def test_attach_observer(self):
        """Test attaching an observer"""
        subject = Subject()
        observer = TestObserver()

        subject.attach(observer)
        assert observer in subject._observers

    def test_attach_duplicate_observer(self):
        """Test that same observer is not attached twice"""
        subject = Subject()
        observer = TestObserver()

        subject.attach(observer)
        subject.attach(observer)

        assert subject._observers.count(observer) == 1

    def test_detach_observer(self):
        """Test detaching an observer"""
        subject = Subject()
        observer = TestObserver()

        subject.attach(observer)
        subject.detach(observer)

        assert observer not in subject._observers

    def test_detach_nonexistent_observer(self):
        """Test detaching an observer that was never attached"""
        subject = Subject()
        observer = TestObserver()

        # Should not raise error
        subject.detach(observer)

    def test_notify_observers(self):
        """Test notifying observers"""
        subject = Subject()
        observer1 = TestObserver()
        observer2 = TestObserver()

        subject.attach(observer1)
        subject.attach(observer2)

        subject.notify('test_event', {'key': 'value'})

        assert len(observer1.events) == 1
        assert observer1.events[0]['event'] == 'test_event'
        assert observer1.events[0]['data'] == {'key': 'value'}

        assert len(observer2.events) == 1
        assert observer2.events[0]['event'] == 'test_event'

    def test_notify_with_no_data(self):
        """Test notifying without data"""
        subject = Subject()
        observer = TestObserver()

        subject.attach(observer)
        subject.notify('simple_event')

        assert len(observer.events) == 1
        assert observer.events[0]['data'] is None

    def test_multiple_notifications(self):
        """Test multiple notifications"""
        subject = Subject()
        observer = TestObserver()

        subject.attach(observer)

        subject.notify('event1', 'data1')
        subject.notify('event2', 'data2')
        subject.notify('event3', 'data3')

        assert len(observer.events) == 3
        assert observer.events[0]['event'] == 'event1'
        assert observer.events[1]['event'] == 'event2'
        assert observer.events[2]['event'] == 'event3'
