class TodoListApp extends React.Component {
  constructor(props) {
    super(props) // props inherit their own methods
    this.state = {
      items: [],
      text: ''
    };

    this.onChange = this.onChange.bind(this);
    this.onSubmit = this.onSubmit.bind(this);
  }

  onChange(evt) {
    // Need to use setState to change state (setState is a react method)
    // React is smart enough to check if the state changed
    this.setState({
      text: evt.target.value      
    });
  }

  onSubmit(evt) {
    // prevents page from submiting form so it doesn't go back to the server
    evt.preventDefault() 
    if (this.state.text.length == 0) {
      return;
    }

    // Add this.state.text to this.state.items
    const newItem = {
      text: this.state.text,
      id: Date.now(),
      completed: false
    };
    this.setState({
      // concat is like push but it constructs a new array and returns their
      // reference to that array
      items: this.state.items.concat(newItem),
      text: ''
    });
  }

  // {} allows us to use javascript within JSX
  // items={this.state.items} pushes down props
  render () {
    return (
      <div>
        <h3>TODO LIST</h3>
        <TodoList items={this.state.items}/>
          <form onSubmit={this.onSubmit}>
            <label>
              What needs to be done.
            </label>
            <input 
              id="new-todo-item" 
              onChange={this.onChange}
              value={this.state.text} />
            <button>
              Add #{this.state.items.length +1}
            </button>
          </form>
      </div>
    );
  }
}


class TodoList extends React.Component {
  render () {
    let lis = '';
    for (let i=0; i<this.props.items.length; i++) {
      lis += <li>{this.props.items[i].text}</li>;
    }
    return (
      /*
      <ul>
        {this.props.items.map(item => {
          <li key={item.id}>{item.text}</li>
        })}
      </ul>
      */

      <ul>
        {lis}
      </ul>
    );
  }
}

const container = document.getElementById('todo-app');
const root = ReactDOM.createRoot(container);
root.render(<TodoListApp />);
