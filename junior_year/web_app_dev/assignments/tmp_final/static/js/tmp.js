class Login extends React.Component {

    sendLoginRequest() {
        let formData = new FormData( document.querySelector('#login-form') );
        fetch('/api/login/', {
            method: 'POST',
            body: formData
        })
        .then(result => result.text())
        .then(
            (result) => {
                if (result == 'ok') {
                    this.props.onLogin();
                }
                else {
                    alert('Bad username/password combo');
                }
            },
            (error) => {
                alert('General login error');
            }
        )
    }

    render() {
        return (
            <form id="login-form">
             <input
                name="username"
                id="username"
                type="text"
                placeholder="username" />
             <input
                name="password"
                id="password"
                type="password"
                placeholder="password" />
             <br />
             <button
                id="login-button"
                onClick={(evt) => {
                    evt.preventDefault();
                    this.sendLoginRequest();
                }}>
               Login
             </button>
            </form>
        );
    }
}

class Avengers extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            avengers: [],
            isLoaded: false,
            error: null,
        };
    }

    componentDidMount() {
        fetch('/api/avengers')
        .then(result => result.json())
        .then(
            (result) => {
                this.setState({
                    avengers: result,
                    isLoaded: true
                });
            },
            (error) => {
                this.setState({
                    error: error,
                    isLoaded: true
                });
            }
        )
    }

    render() {
        if (this.state.error) {
            return (
                <div>Error: Avengers must have been snapped by Thanos.</div>
            );
        }
        else if (!this.state.isLoaded) {
            return (
                <div>Waiting for Avengers to assemble...</div>
            );
        }
        else {
            return (
                <div className="avengers">
                    <h1>Avengers Assembled!</h1>
                    <ul>
                        {this.state.avengers.map(hero => {
                            return (
                             <li key={hero}>
                                {hero}
                             </li>
                            );
                        })};
                    </ul>
                </div>
            );
        }
    }
}

class App extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            view: 'login'
        };
    }

    onLogin() {
        this.setState({
            view: 'avengers'
        });
    }

    render() {
        let component = <Login onLogin={() => this.onLogin()} />;
        if (this.state.view == 'avengers') {
            component = <Avengers />;
        }

        return (
            <div className="app">
              {component}
            </div>
        );
    }
}

const container = document.querySelector('#app');
const root = ReactDOM.createRoot(container);
root.render(<App />);
