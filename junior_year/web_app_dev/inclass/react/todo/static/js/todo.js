class TodoListApp extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      items: [],
      text: ''
    };

    this.onChange = this.onChange.bind(this);
    this.onSubmit = this.onSubmit.bind(this);
    this.onCrossout = this.onCrossout.bind(this);
    this.onDelete = this.onDelete.bind(this);
  }

  onChange(evt) {
    this.setState({
      text: evt.target.value
    });
  }

  onCrossout(itemid) {
    let newItems = [];
    this.state.items.forEach((item) => {
      if (item.id == itemid) {
        item.completed = !item.completed;
      }
      if (item.completed) {
        item.style = { textDecoration: 'line-through' };
      }
      else {
        item.style = { };
      }
      newItems.push(item);
    });
    this.setState({ items: newItems });
  }

  onDelete(itemid) {
    this.setState({
      items: this.state.items.filter(item => {
        return item.id != itemid
      })
    });
  }

  onSubmit(evt) {
    evt.preventDefault();
    if (this.state.text.length == 0) {
      return;
    }
    // Add this.state.text to this.state.items
    const newItem = {
      text: this.state.text,
      id: Date.now(),
      completed: false,
      style: { }
    };
    this.setState({
      items: this.state.items.concat(newItem),
      text: ''
    });
  }

  render() {
    return (
      <div>
        <h3>TODO LIST</h3>
        <TodoList
          items={this.state.items}
          onCrossout={this.onCrossout}
          onDelete={this.onDelete}
        />
        <form onSubmit={this.onSubmit}>
          <label>
            What needs to be done.
          </label>
          <input
            id="new-todo-item"
            onChange={this.onChange} 
            value={this.state.text}
          />
          <button>
            Add #{this.state.items.length + 1}
          </button>
        </form>
      </div>
    );
  }
}

class TodoList extends React.Component {
  render() {
    return (
      <ul>
      {this.props.items.map(item => {
        return (
          <li key={item.id}>
            <span
              style={item.style}
              onClick={() => this.props.onCrossout(item.id)}>
              {item.text}
            </span>
            <button
              onClick={() => this.props.onDelete(item.id)}>
              Delete
            </button>
          </li>
        );
      })}
      </ul>
    );
  }
}

const container = document.getElementById('todo-app');
const root = ReactDOM.createRoot(container);
root.render(<TodoListApp />);
